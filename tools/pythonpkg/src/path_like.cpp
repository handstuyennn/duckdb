#include "duckdb_python/path_like.hpp"
#include "duckdb_python/pyrelation.hpp"
#include "duckdb_python/pyconnection.hpp"
#include "duckdb/common/string_util.hpp"
#include "duckdb_python/pyfilesystem.hpp"
#include "duckdb_python/filesystem_object.hpp"

namespace duckdb {

PathLike PathLike::Create(const py::object &object, DuckDBPyConnection &connection) {
	PathLike result;
	auto &import_cache = *DuckDBPyConnection::ImportCache();
	if (py::isinstance<py::str>(object)) {
		result.str = py::str(object);
		return result;
	}
	if (import_cache.pathlib().Path.IsInstance(object)) {
		result.str = py::str(object);
		return result;
	}
	// Make sure that the object filesystem is initialized and registered
	auto &fs = connection.GetObjectFileSystem();
	result.str = StringUtil::Format("%s://%s", "DUCKDB_INTERNAL_OBJECTSTORE", StringUtil::GenerateRandomName());
	fs.attr("add_file")(object, result.str);
	result.dependency = make_unique<PythonDependencies>(make_unique<FileSystemObject>(fs, result.str));
	return result;
}

} // namespace duckdb
