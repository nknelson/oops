#include <multimap>
#include <vector>
#include <queue>

std::vector<std::vector<std::queue<uint32_t>>> votes;
//typedef std::vector<std::vector<std::queue<uint32_t>>> Votes_t;

void populate_votes(Votes_t & votes, std::string & ballot, uint32_t &ballot_count) {
    // Neil to finish
    ++ballot_count;
    ballot >> candidate; // PSEUDO-CODE!   "pop" first number from the ballot; i.e if ballot is "1 2 3" then candidate=1
    std::queue vote_queue;
    while (ballot >> next_vote) {
        vote_queue.push_back(next_vote);
    }
    votes[cadidate].push_back(vote_queue);
}

void process_votes(Votes_t & votes, uint32_t win_count) {
    // Jyotsna to finish
    std::multimap<uint32_t, uint32_t> candidates_mmap;
    uint32_t max = 0;
    uint32_t min = std::infinity;
    bool done = false;
    while (!done) {
        for (uint32_t i=1; i<=votes.size()-1 ; i++) {
            uint32_t vote_count = votes[i].size();
            if (vote_count > 0) {
                candidates_mmap.insert(std::make_pair(i, vote_count));
            }
            if (vote_count>max) {
                max = vote_count;
            }
            if (vote_count < min) {
                min = vote_count;
            }
        }
        if (max == min) {
            // TIE
            // print results
            return;
        }
        else if (max >= win_count) {
            // clear winner
            // print results
            return;
        }
        else {
            // redistribute mins' votes
            for (auto min:get_the_minima) {
                redistribute(votes, min);
            }
        }
    }
}

void redistribute(Votes_t & votes, uint32_t loser) {
    // Jyotsna to do
}

main() {
    // Neil to finish
    // get total number of candidates;
    votes.resize(total_number_of_candidates+1);
}
