// Scaffolding originally generated from include/server.x.
// Edit to add functionality.

#include "server/serverimpl.hh"

static bool check_valid_path(const std::string path) {
	int length = path.length();
	if((path[0] != '/') || (path[length-1] == '/')) {
		return false;
	}

	for(char ch : path) {
		if(!(ch == '/' || ch == '_' || (ch >= '0' && ch <= '9')
			 || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')))
			return false;
	}

	return true;
}

static const std::string getParentPath(const std::string path) {
	int pos = path.find_last_of('/');
	if(pos != 0) {
		return path.substr(0, pos);
	}
	else {
		return "";
	}
}

static bool check_exist_parent(ServerDB db, const std::string path) {
	std::string parentPath = getParentPath(path);
	if(parentPath != "") {
		return db.hasKey(parentPath);
	}

	return true;
}

std::unique_ptr<Result>
api_v1_server::create(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<Result> res(new Result);
  
  // Fill in function body here
  
  return res;
}

std::unique_ptr<Result>
api_v1_server::remove(std::unique_ptr<longstring> arg)
{
  std::unique_ptr<Result> res(new Result);
  
  // Fill in function body here
  
  return res;
}

std::unique_ptr<Result>
api_v1_server::set(std::unique_ptr<kvpair> arg)
{
  std::unique_ptr<Result> res(new Result);
  
  // Fill in function body here
  
  return res;
}
