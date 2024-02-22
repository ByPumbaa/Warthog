#pragma once
#include "api/types/all.hpp"
#include "chainserver/mining_subscription.hpp"
#include "communication/mining_task.hpp"
#include <list>
#include <memory>
#include <set>
#include <string>
#include <thread>
#include <variant>
#include <vector>

namespace uvw {
class loop;
class async_handle;
class tcp_handle;
};
class StratumServer;
namespace stratum {
namespace messages {
    struct MiningSubscribe;
    struct MiningAuthorize;
    struct MiningSubmit;
}

class Connection : public std::enable_shared_from_this<Connection> {
    struct Writer {
        Connection& c;
        template <typename T>
        Writer& operator<<(T&& t)
        {
            c.write_line(t.to_string());
            return *this;
        }
    };
    friend class ::StratumServer;
    friend struct Writer;

public:
    Connection(std::shared_ptr<uvw::tcp_handle> newHandle, StratumServer& server)
        : handle(std::move(newHandle))
        , server(server)
    {
    }

    void on_message(std::string_view msg);
    ~Connection();

    void on_append_result(int64_t stratumId, tl::expected<void, int32_t>);
private:
    void handle_message(messages::MiningSubscribe&& s);
    void handle_message(messages::MiningSubmit&& m);
    void handle_message(messages::MiningAuthorize&& m);
    void send_work(std::string jobId, const Block& block, bool clean);
    void shutdown();
    void write_line(const std::string& line);
    void process_line();
    Writer write() { return { *this }; }

    struct Authorized {
        Address address;
        std::string worker;
    };
    bool fresh { true };
    std::optional<Authorized> authorized;
    std::string stratumLine;
    std::shared_ptr<uvw::tcp_handle> handle;
    StratumServer& server;
};

}

class StratumServer {
    friend class stratum::Connection;
    struct AddressData {
        using Subscription = mining_subscription::MiningSubscription;
        bool clean { true };
        std::vector<stratum::Connection*> connections;
        std::map<std::string, Block> blocks;
        Subscription subscription;
        AddressData(std::function<Subscription()>);
        void clear()
        {
            blocks.clear();
            clean = true;
        }
    };
    struct SubscriptionFeed {
        Address address;
        MiningTask t;
    };
    struct ShutdownEvent {
    };
    struct AppendResult {
        std::weak_ptr<stratum::Connection> p;
        int64_t stratumId;
        tl::expected<void, int32_t> result;
    };
    using Event = std::variant<SubscriptionFeed, ShutdownEvent,AppendResult>;
    void push(Event e);
    void handle_events();
    void handle_event(SubscriptionFeed&&);
    void handle_event(ShutdownEvent&&);
    void handle_event(AppendResult&&);

    void acceptor(std::string bind, uint16_t port);
    void link_authorized(const Address&, stratum::Connection*);
    void unlink_authorized(const Address&, stratum::Connection*);

    std::optional<Block> get_block(Address,std::string jobId);
public:
    StratumServer(std::string bind = "127.0.0.1", uint16_t port = 3456);
    ~StratumServer();
    void shutdown();
    void request_mining();
    void on_mining_task(Address, MiningTask&&);
    void on_append_result(AppendResult);

private:
    std::map<Address, AddressData> addressData;
    std::list<std::shared_ptr<stratum::Connection>> connections;
    const std::shared_ptr<uvw::loop> loop;

    std::thread t;
    std::mutex m;
    std::vector<Event> events;
    const std::shared_ptr<uvw::async_handle> async;
};
