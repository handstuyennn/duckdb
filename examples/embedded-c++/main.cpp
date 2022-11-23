#include "duckdb.hpp"

#include <iostream>

using namespace duckdb;

int main() {
	DuckDB db(nullptr);

	Connection con(db);

	// auto extrv1 = con.Query("INSTALL 'fts';");
	// extrv1->Print();
	// auto extrv2 = con.Query("LOAD 'fts';");
	// extrv2->Print();

	auto rv_ext = con.Query("select * From duckdb_extensions();");
	rv_ext->Print();

	auto rv1 = con.Query("CREATE TABLE geometries(i1 INTEGER, i2 INET, g Geometry)");
	rv1->Print();
	// con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2', ST_MakeLine([ST_MAKEPOINT(1,2),
	// ST_MAKEPOINT(3,455)]))"); con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2',
	// ST_MakePolygon('LINESTRING(0.0 0.0, 1.0 0.0, 1.0 2.0, 0.0 2.0, 0.0 0.0)'))");
	con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2', ST_MakePolygon('LINESTRING (0 0, 0 150, 150 150, 150 "
	          "0, 0 0)', ['LINESTRING(20 20, 50 20, 50 50, 20 50, 20 20)'::GEOMETRY, 'LINESTRING (90 100, 90 80, 110 "
	          "80, 110 100, 90 100)'::GEOMETRY]))");
	// con.Query("INSERT INTO geometries VALUES (2, '127.0.0000.3', ST_MakeLine(ST_MAKEPOINT(1,2),
	// ST_MAKEPOINT(3,4)))"); auto rv2 = con.Query("INSERT INTO geometries VALUES (3, '127.0.0000.1', 'POINT(0 1)')");
	// rv2->Print();
	// con.Query("INSERT INTO geometries VALUES (4, '127.0.0000.3', '{\"type\":\"Point\",\"coordinates\":[0,5]}')");
	// con.Query("INSERT INTO geometries VALUES (5, '127.0.0000.4', '010100000000000000000000000000000000004940')");
	// auto irv = con.Query("INSERT INTO geometries VALUES (6, '127.0.0000.4',
	// '01020000000400000000000000000000000000000000000000000000000000f03f000000000000f03f0000000000000040000000000000f03f00000000000000400000000000000040')");
	// con.Query("INSERT INTO geometries VALUES (7, '127.0.0000.4',
	// '010C00000002000000010A000000020000000108000000050000000000000000000000000000000000000000000000000010400000000000000000000000000000104000000000000010400000000000000000000000000000104000000000000000000000000000000000010200000004000000000000000000F03F000000000000F03F000000000000084000000000000008400000000000000840000000000000F03F000000000000F03F000000000000F03F01030000000200000004000000000000000000244000000000000024400000000000002C40000000000000284000000000000026400000000000002440000000000000244000000000000024400400000000000000000026400000000000002640000000000000274000000000000026400000000000002640000000000000274000000000000026400000000000002640')");
	// auto result = con.Query("SELECT i1, i2, ST_ASTEXT(g) FROM geometries");
	// // auto result = con.Query("SELECT i1, g::VARCHAR FROM geometries");
	// result->Print();

	// auto rv3 = con.Query("SELECT ST_DISTANCE(ST_MakePoint(-7.1043443253471, 43.3150676015829),
	// ST_MakePoint(-70.1043443253471, 42.3150676015829), true);"); rv3->Print();

	// auto rv4 = con.Query("SELECT ST_DISTANCE(ST_MakePoint(-7.1043443253471, 43.3150676015829),
	// ST_MakePoint(-70.1043443253471, 42.3150676015829), false);"); rv4->Print();

	// auto rv5 = con.Query("SELECT ST_DISTANCE(ST_MakePoint(-7.1043443253471, 43.3150676015829),
	// ST_MakePoint(-70.1043443253471, 42.3150676015829));"); rv5->Print();

	// auto rv6 = con.Query("SELECT
	// ST_ASTEXT(ST_GeomFromWKB('\\x01\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x14@'::BLOB));");
	// rv6->Print();

	// auto rv7 = con.Query("SELECT
	// '\\x01\\x01\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x00\\x14@'::BYTEA;");
	// rv7->Print();

	// con.Query("CREATE TABLE geometries (g Geometry);");
	// con.Query("INSERT INTO geometries VALUES('{\"type\":\"Point\",\"coordinates\":[30,10.2323]}'),
	// ('{\"type\":\"Point\",\"coordinates\":[-71.064544,10.2323]}'),
	// ('{\"type\":\"Point\",\"coordinates\":[30,43.28787]}');");
	// // con.Query("INSERT INTO geometries VALUES(''::GEOMETRY), (NULL::GEOMETRY), ('POINT(10 54)');");
	// auto rv8 = con.Query("SELECT g::VARCHAR FROM geometries;");
	// rv8->Print();

	auto rv9 = con.Query("SELECT ST_AsText(ST_PointN(ST_GeomFromText('CIRCULARSTRING(1 2, 3 2, 1 2)'), 2));");
	rv9->Print();

	// auto rv10 = con.Query("SELECT ST_MAKEPOINT(2.22, 2.33);");
	// rv10->Print();
}
