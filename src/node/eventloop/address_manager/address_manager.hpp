#pragma once
#include "../types/conndata.hpp"
#include "asyncio/helpers/per_ip_counter.hpp"
#include "connection_schedule.hpp"
#include "expected.hpp"
#include "flat_address_set.hpp"
#include "general/tcp_util.hpp"
#include <chrono>
#include <map>
#include <set>
#include <vector>
class Conref;
class TCPConnection;
struct Inspector;

namespace address_manager {

class AddressManager {
    using time_point = std::chrono::steady_clock::time_point;

public:
    friend struct ::Inspector;

private:
    class ConrefIter : public Coniter {
    public:
        Conref operator*() { return Conref { *this }; }
    };
    struct All {
        const AddressManager& ref;
        struct End {
        };
        struct Iterator {
            ConrefIter iter;
            const AddressManager& ref;
            Iterator(ConrefIter iter, const AddressManager& ref)
                : iter(iter)
                , ref(ref)
            {
                find_next();
            }
            Iterator& operator++()
            {
                ++iter;
                find_next();
                return *this;
            }
            Conref operator*() { return iter; }
            bool operator==(End)
            {
                return iter == ref.conndatamap.end();
            }

        private:
            void find_next();
        };
        auto begin() const { return Iterator {
            { ref.conndatamap.begin() },
            ref
        }; }
        auto end() const { return End {}; }
        bool empty() { return begin() == end(); };
    };
    struct Initialized {
        const AddressManager& ref;
        struct End {
        };
        struct Iterator {
            ConrefIter iter;
            const AddressManager& ref;
            Iterator(ConrefIter iter, const AddressManager& ref)
                : iter(iter)
                , ref(ref)
            {
                find_next();
            }
            Iterator& operator++()
            {
                ++iter;
                find_next();
                return *this;
            }
            Conref operator*() { return iter; }
            bool operator==(End)
            {
                return iter == ref.conndatamap.end();
            }

        private:
            void find_next();
        };
        auto begin() const { return Iterator {
            { ref.conndatamap.begin() },
            ref
        }; }
        auto end() const { return End {}; }
        bool empty() { return begin() == end(); };
    };
    struct EvictionCandidate {
        Conref evictionCandidate;
    };

public:
    //////////////////////////////
    // public methods
    
    // constructor
    AddressManager(PeerServer& peerServer, const std::vector<EndpointAddress>& v);
    void start();

    // for range-based access
    Initialized initialized() const { return { *this }; }
    All all() const { return { *this }; }

    void outbound_failed(const ConnectRequest& r);

    // access by connection Id
    std::optional<Conref> find(uint64_t id);

    size_t size() const { return conndatamap.size(); }

    // erase/insert
    bool erase(Conref); // returns whether is pinned
    [[nodiscard]] tl::expected<EvictionCandidate, int32_t> prepare_insert(const std::shared_ptr<ConnectionBase>&);
    Conref insert_prepared(const std::shared_ptr<ConnectionBase>&, HeaderDownload::Downloader&, BlockDownload::Downloader&, Timer&);

    // access queued

    [[nodiscard]] std::vector<EndpointAddress> sample_verified(size_t N)
    {
        return connectionSchedule.sample_verified(N);
    }

    void garbage_collect();

    void start_scheduled_connections();
    [[nodiscard]] std::optional<time_point> pop_scheduled_connect_time();

private:
    void start_connection(const ConnectRequest&);

    bool is_own_endpoint(EndpointAddress a);
    void insert_additional_verified(EndpointAddress);
    std::optional<EvictionCandidate> eviction_candidate() const;

private:
    // data
    FlatAddressSet failedAddresses;

    // maps/sets by EndpointAddress
    // std::set<EndpointAddress> unverifiedAddresses;
    // VerifiedMap verified;
    // PinnedMap pinned;

    std::vector<EndpointAddress> additionalEndpoints;
    std::vector<EndpointAddress> outboundEndpoints;
    std::vector<Conref> inboundConnections;
    ConnectionSchedule connectionSchedule;

    mutable Conndatamap conndatamap;
    std::vector<Conref> delayedDelete;
    PerIpCounter ipCounter;
};
}
