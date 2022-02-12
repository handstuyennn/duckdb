#include "duckdb/function/scalar/geometry_functions.hpp"
#include "postgis.hpp"

namespace duckdb {

struct MakePointBinaryOperator {
	template <class TA, class TB, class TR>
	static inline TR Operation(TA point_x, TB point_y) {
		Postgis postgis;
		auto gser = postgis.LWGEOM_makepoint(point_x, point_y);
		auto base = postgis.LWGEOM_base(gser);
		auto size = postgis.LWGEOM_size(gser);
		postgis.LWGEOM_free(gser);
		return string_t(base, size);
	}
};

struct MakePointTernaryOperator {
	template <class TA, class TB, class TC, class TR>
	static inline TR Operation(TA point_x, TB point_y, TC point_z) {
		Postgis postgis;
		auto gser = postgis.LWGEOM_makepoint(point_x, point_y, point_z);
		auto base = postgis.LWGEOM_base(gser);
		auto size = postgis.LWGEOM_size(gser);
		postgis.LWGEOM_free(gser);
		return string_t(base, size);
	}
};

template <typename TA, typename TB, typename TR>
static void MakePointBinaryExecutor(Vector &point_x, Vector &point_y, Vector &result, idx_t count) {
	BinaryExecutor::ExecuteStandard<TA, TB, TR, MakePointBinaryOperator>(point_x, point_y, result, count);
}

template <typename TA, typename TB, typename TC, typename TR>
static void MakePointTernaryExecutor(Vector &point_x, Vector &point_y, Vector &point_z, Vector &result, idx_t count) {
	TernaryExecutor::Execute<TA, TB, TC, TR>(point_x, point_y, point_z, result, count,
	                                         MakePointTernaryOperator::Operation<TA, TB, TC, TR>);
}

static void MakePointFunction(DataChunk &args, ExpressionState &state, Vector &result) {
	auto &point_x_arg = args.data[0];
	auto &point_y_arg = args.data[1];
	if (args.data.size() == 2) {
		MakePointBinaryExecutor<double, double, string_t>(point_x_arg, point_y_arg, result, args.size());
	} else if (args.data.size() == 3) {
		auto &point_z_arg = args.data[2];
		MakePointTernaryExecutor<double, double, double, string_t>(point_x_arg, point_y_arg, point_z_arg, result,
		                                                           args.size());
	}
}

void MakePointFun::RegisterFunction(BuiltinFunctions &set) {
	ScalarFunctionSet make_point("st_makepoint");
	make_point.AddFunction(
	    ScalarFunction({LogicalType::DOUBLE, LogicalType::DOUBLE}, LogicalType::GEOMETRY, MakePointFunction));
	make_point.AddFunction(ScalarFunction({LogicalType::DOUBLE, LogicalType::DOUBLE, LogicalType::DOUBLE},
	                                      LogicalType::GEOMETRY, MakePointFunction));
	set.AddFunction(make_point);
}

} // namespace duckdb