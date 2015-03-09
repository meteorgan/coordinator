// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#include<iostream>
#include<set>

#include "server/serverimpl.hh"


api_v1_server::api_v1_server() : db("kvstore.db") {
	if(!db.hasKey("/")) {
		db.set("/", "");
	}
}

static bool check_valid_path(const std::string& path) {
	int length = path.length();
	if((path[0] != '/') || ((path.size()) >1 && (path[length-1] == '/'))) {
		return false;
	}

	for(char ch : path) {
		if(!(ch == '/' || ch == '_' || (ch >= '0' && ch <= '9')
			 || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
			return false;
	}

	return true;
}

static const std::string getParentPath(const std::string& path) {
	int pos = path.find_last_of('/');
	if(pos != 0) {
		return path.substr(0, pos);
	}
	else {
		return "";
	}
}

static bool check_exist_parent(ServerDB& db, const std::string& path) {
	std::string parentPath = getParentPath(path);
	if(parentPath != "") {
		return db.hasKey(parentPath);
	}

	return true;
}


std::unique_ptr<Result>
api_v1_server::create(std::unique_ptr<kvpair> arg)
{
	std::unique_ptr<Result> res(new Result(3));

	std::string key = arg->key;
	std::string value = arg->val;

	res->error() = ServerError::NONE;
	if(check_valid_path(key)) {
		bool hasKey = db.hasKey(key);
		if(hasKey) {
			res->error() = ServerError::KEY_DUPLICATE;
			std::cerr << "duplicate key: " << key << std::endl;
		}
		else {
			if(check_exist_parent(db, key)) {
				db.set(key, value);
				std::cout << "add key: " << key << " with value: " << value << std::endl;
			}
			else {
				res->error() = ServerError::KEY_NO_PARENT;
				std::cerr << "key: " << key << " has no parent!" << std::endl;
			}
		}
	}
	else {
		res->error() = ServerError::KEY_MALFORMED;
		std::cerr << "malformed key: "<< key << std::endl;
	}

	return res;
}

std::unique_ptr<Result>
api_v1_server::set(std::unique_ptr<kvpair> arg)
{
	std::unique_ptr<Result> res(new Result(3));
	std::string key = arg->key;
	std::string val = arg->val;

	res->error() = ServerError::NONE;
	if(check_valid_path(key)) {
		if(db.hasKey(key)) {
			db.set(key, val);
			std::cout << "set key: " << key << " with value: " << val << std::endl;
		}
		else {
			res->error() = ServerError::KEY_NOT_FOUND_ERROR;
			std::cerr << "key: " << key << " not found." << std::endl;
		}
	}
	else {
		res->error() = ServerError::KEY_MALFORMED;
		std::cerr << "malformed key: " << key << std::endl;
	}

	return res;
}

std::unique_ptr<Result>
api_v1_server::get(std::unique_ptr<longstring> arg) {
	std::unique_ptr<Result> res(new Result);

	std::string& path = *arg;
	if(check_valid_path(path)) {
		if(db.hasKey(path)) {
			res->discriminant(1);
			res->val() = db.get(path);
			std::cout << "get key: " << path << " with value: " << res->val() << std::endl;
		}
		else {
			res->discriminant(3);
			res->error() = ServerError::KEY_NOT_FOUND_ERROR;
			std::cerr << "key: " << path << " not found." << std::endl;
		}
	}
	else {
		res->discriminant(3);
		res->error() = ServerError::KEY_MALFORMED;
		std::cerr << "malformed key: " << path << std::endl;
	}

	return res;
}

std::unique_ptr<Result>
api_v1_server::remove(std::unique_ptr<longstring> arg)
{
	std::unique_ptr<Result> res(new Result);
	std::string& path = *arg;

	res->error() = ServerError::NONE;
	if(check_valid_path(path)) {
	if(db.hasKey(path)) {
		if(db.list(path).size() == 0) {
			db.remove(path);
			std::cout << "remove key: " << path << std::endl;
		}
		else {
			res->error() = ServerError::KEY_HAS_CHILDREN;
			std::cout << "key has children, cannot remove." << std::endl;
		}
	}
	else {
		res->error() = ServerError::KEY_NOT_FOUND_ERROR;
		std::cout << "key: " << path << " not found." << std::endl;
	}
	}
	else {
		res->error() = ServerError::KEY_MALFORMED;
		std::cerr << "malformed key: " << path << std::endl;
	}

	return res;
}

static std::string getSubDir(const std::string parentPath, const std::string& path) {
	int size = parentPath.size();
	std::string prefix = parentPath;
	if(parentPath.at(size-1) != '/') {
		prefix = prefix + "/";
	}
	int startPos = path.find(prefix) + prefix.size();
	std::string::size_type endPos = path.find("/", startPos);
	if(endPos == std::string::npos) {
		endPos = path.size();
	}

	return path.substr(startPos, endPos-startPos);
}

std::unique_ptr<Result>
api_v1_server::list(std::unique_ptr<longstring> arg) {
	std::unique_ptr<Result> res(new Result);
	std::string& path = *arg;

	if(check_valid_path(path)) {
		if(db.hasKey(path)) {
			std::set<std::string> subKeys = db.list(path);
			res->discriminant(2);
			for(auto &key : subKeys) {
				std::string subPath = getSubDir(path, key);
				res->keys().push_back(subPath);
				std::cout << key << " " << subPath << std::endl;
			}
			std::cout << "list key: " << path << "'s subKey" << std::endl;
		}
		else {
			res->discriminant(3);
			res->error() = ServerError::KEY_NOT_FOUND_ERROR;
			std::cout << "key: " << path << " not found." << std::endl;
		}
	}
	else {
		res->discriminant(3);
		res->error() = ServerError::KEY_MALFORMED;
		std::cerr << "malformed key: " << path << std::endl;
	}

	return res;
}
