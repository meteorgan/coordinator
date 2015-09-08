% #include "server.hh"

/*
 * 2PC
 */

typedef unsigned hyper ParticipantId;
typedef unsigned hyper OpInt;


enum OpType {
	CREATE,
	SET,
	REMOVE
};

enum RequestResponse {
	VOTE_COMMIT,
	VOTE_ABORT
};

enum CommitOp {
	GLOABL_COMMIT,
	GLOBAL_ABORT
};

struct RequestInfo {
	kvpair kv;
	OpType opType;
	OpInt opNum;
	ParticipantId participantId;
};

struct ReponseInfo {
	OpInt opNum;
	RequestResponse response;
	ParticipantId participantId;
};

struct CommitInfo {
	CommitOp commitOp;
	OpInt opNum;
	ParticipantId participantId;
};

program participant_api {
	version participantApi_v1 {
		void request_vote(RequestInfo) = 1;
		void response_vote(ReponseInfo) = 2;
        void request_commit(CommitInfo) = 3;
	} = 1;
} = 0x40048088;