typedef string longstring<>;

struct kvpair {
	string key<512>;
	string val<>;
};

enum ServerError {
	NONE,
	KEY_NOT_FOUND_ERROR,
	KEY_NO_PARENT,
	KEY_HAS_CHILDREN,
	KEY_MALFORMED,
	KEY_DUPLICATE,
	QUORUM_NOT_REACHED
};

union Result switch(unsigned discriminant) {
	case 1:
		string val<>;
	case 2:
		longstring keys<>;
	default:
		ServerError error;
};

program server_api {
  version api_v1 {
	Result create(kvpair) = 1;
	Result remove(longstring) = 2;
	Result set(kvpair) = 3;
	Result get(longstring) = 4;
	Result list(longstring) = 5;
  } = 1;
} = 0x40048086;