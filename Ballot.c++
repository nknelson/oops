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

void process_votes(Votes_t & votes, uint32_t win_threshold) {
  // Jyotsna to finish
  typedef std::multimap<uint32_t, uint32_t> Cand_MultiMap;
  
  uint32_t max = 0;
  uint32_t min = 0xffffffff;
  while (true) {
    Cand_MultiMap candidates_mmap;
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
      uint32_t cand_num = (candidates_mmap.find(max)).second;
      //assert (cand_num < candidate_names.size();
      std::cout << candidate_names[cand_num] << std::endl;
      return;
    }
    else if (max == min) {
      // TIE
      // print results
      std::pair<Cand_MultiMap::iterator, Cand_MultiMap::iterator> ii =
	candidates_mmap.equal_range(max);
      for (Candidates_Mmap::iterator it = ii.first; it != ii.second; ++it) {
	uint32_t cand_num = it->second;
	std::cout << candidate_names[cand_num] << std::endl;
      }
      return;
    }
    else {
      std::pair<Cand_MultiMap::iterator, Cand_MultiMap::iterator> ii =
	candidates_mmap.equal_range(min);
      for (Candidates_Mmap::iterator it = ii.first; it != ii.second; ++it) {
	redistribute (votes, it->second);
      }

    }
  }
}

void redistribute(Votes_t & votes, uint32_t loser) {
  // Jyotsna to do
  std::vector<std::queue<uint32_t>> & loser_votes = votes[loser];
  for (auto & ballot : votes[loser]) {
    // assert (ballot.empty() == false);
    uint32_t lucky_guy = ballot.front();
    ballot.pop();
    votes[lucky_guy].push_back(ballot);
  }
  votes[loser].clear();
  
}

main() {
    // Neil to finish
    // get total number of candidates;
    votes.resize(total_number_of_candidates+1);
}
