
typedef string longstring<>;

struct kvpair {
	string key<512>;
	string val<>;
};

enum ServerError {
	KEY_NOT_FOUND,
	NO_PARENT,
	HAS_CHILDREN,
	MALFORMED_KEY
};

union Result switch(unsigned discriminant) {
	case 1:
		string val<>;
	case 2:
		longstring key<>;
	case 3:
		ServerError error;
};

program server_api {
  version api_v1 {
	Result create(kvpair) = 1;
	Result remove(longstring) = 2;
	Result set(kvpair) = 3;
    // TODO: Fill me in
  } = 1;
} = 0x40048086;