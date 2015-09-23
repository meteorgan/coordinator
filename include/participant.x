% #include "two_phrase_commit_common.hh"

/*
 * 2PC, participant
 */

program participant_api {
	version participant_api_v1 {
		void request_vote(RequestInfo) = 1;
		void request_response(ResponseInfo) = 2;
        void request_commit(CommitInfo) = 3;
	} = 1;
} = 0x40048088;