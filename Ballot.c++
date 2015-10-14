#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <unordered_map>      // unordered multimap
#include <map>      // multimap
#include <vector>
#include <queue>
#include <cstdint>

typedef std::vector<std::vector<std::queue<uint32_t>>> Votes_t;

void redistribute(Votes_t & votes, uint32_t loser) {
    // Jyotsna to do
    std::vector<std::queue<uint32_t>> & loser_votes = votes[loser];
    for (auto & ballot : votes[loser]) {
        // assert (ballot.empty() == false);
        uint32_t lucky_guy = ballot.front();
        ballot.pop();
        if (votes[lucky_guy].size() > 0) {
            votes[lucky_guy].emplace_back(ballot);
        }
    }
    votes[loser].clear();

}

void process_votes(Votes_t & votes, uint32_t win_threshold,
                   std::vector<std::string> candidate_names) {
    typedef std::multimap<uint32_t, uint32_t> Cand_MultiMap;

    uint32_t max = 0;
    uint32_t min = 0xffffffff;
    Cand_MultiMap candidates_mmap;
    while (true) {
        candidates_mmap.clear();
        for (uint32_t i=1; i < votes.size(); ++i) {
            uint32_t vote_count = votes[i].size();
            if (vote_count > 0) {
                candidates_mmap.insert(std::make_pair(vote_count, i));
                if (vote_count > max) {
                    max = vote_count;
                }
                if (vote_count < min) {
                    min = vote_count;
                }
            }
        }

        // XXX win_threshold should be floor, not ceil
        if (max > win_threshold) {
            // clear winner
            // print results
            //assert (candidates_mmap.count(max) == 1);
            uint32_t cand_num = (*(candidates_mmap.find(max))).second;
            //assert (cand_num < candidate_names.size();
            std::cout << candidate_names[cand_num] << std::endl;
            return;
        }
        else if (max == min) {
            // TIE
            // print results
            std::pair<Cand_MultiMap::iterator, Cand_MultiMap::iterator> ii =
                candidates_mmap.equal_range(max);
            for (Cand_MultiMap::iterator it = ii.first; it != ii.second; ++it) {
                uint32_t cand_num = it->second;
                std::cout << candidate_names[cand_num] << std::endl;
            }
            return;
        }
        else {
            if (candidates_mmap.count(min) > 0) {
                std::pair<Cand_MultiMap::iterator, Cand_MultiMap::iterator> ii =
                    candidates_mmap.equal_range(min);
                for (Cand_MultiMap::iterator it = ii.first; it != ii.second; ++it) {
                    redistribute (votes, it->second);
                }
            } else {
                redistribute (votes, (*(candidates_mmap.find(min))).second);
            }

        }
    }
}

void populate_votes(Votes_t & votes, std::string & ballot, const uint32_t num_candidates) {
    std::istringstream sin(ballot);
    uint32_t candidate;
    sin >> candidate; // "pop" first number from the ballot; i.e if ballot is "1 2 3" then candidate=1
    std::queue<uint32_t> vote_queue;
    for (uint32_t j=1; j<num_candidates; j++) {
        uint32_t next_vote;
        sin >> next_vote;
        vote_queue.emplace(next_vote);
    }
    votes[candidate].emplace_back(vote_queue);
    return;
}

void ballot_solve(std::istream & r, Votes_t & votes,
                  std::vector<std::string> & candidate_names) {
    // Read in the first line, which is the total number of test cases
    std::string s;
    getline(r, s);
    uint32_t test_cases;
    std::istringstream sin(s);
    sin >> test_cases;

    // Each test case starts with a blank line
    getline(r, s);

    for (uint32_t j=0; j<test_cases; j++) {
        votes.clear();
        candidate_names.clear();

        // The next line of input is an integer n<=20 indicating the number
        // of candidates
        getline(r, s);
        sin.clear();
        sin.str(s);
        uint32_t num_candidates;
        sin >> num_candidates;

        assert(num_candidates>0 && num_candidates<=20);

        // Candidate 0 has no name
        votes.resize(num_candidates+1);
        candidate_names.push_back("");
        // The next n lines consist of the names of the candidates in order.
        for (uint32_t n=0; n<num_candidates; n++) {
            getline(r, s);
            candidate_names.push_back(s);
        }

        // Up to 1000 lines follow; each contains the contents of a ballot
        uint32_t num_votes = 0;
        do {
            getline(r, s);
            if (r.good()) {
                if (s == "") {
                    break;
                } else {
                    ++num_votes;
                    populate_votes(votes, s, num_candidates);
                }
            } else {
                break;
            }
        } while (true);

        process_votes(votes, num_votes/2, candidate_names);
    }
}

main() {
    Votes_t votes;
    std::vector<std::string> candidates;
    ballot_solve(std::cin, votes, candidates);
    // Neil to finish
    // get total number of candidates;
    return 0;
}
