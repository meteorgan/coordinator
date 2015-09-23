% #include "server.hh"

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

struct CommitRequest {
	kvpair kv;
	OpType opType;
};

struct RequestInfo {
	kvpair kv;
	OpType opType;
	OpInt opNum;
	ParticipantId participantId;
};

struct ResponseInfo {
	OpInt opNum;
	RequestResponse response;
	ParticipantId participantId;
};

struct CommitInfo {
	CommitOp commitOp;
	OpInt opNum;
	ParticipantId participantId;
};