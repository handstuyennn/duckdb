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

	// auto rv1 = con.Query("CREATE TABLE geometries(i1 INTEGER, i2 INET, g Geometry)");
	// rv1->Print();
	// // con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2', ST_MakeLine([ST_MAKEPOINT(1,2),
	// // ST_MAKEPOINT(3,455)]))"); con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2',
	// // ST_MakePolygon('LINESTRING(0.0 0.0, 1.0 0.0, 1.0 2.0, 0.0 2.0, 0.0 0.0)'))");
	// con.Query("INSERT INTO geometries VALUES (1, '127.0.0000.2', ST_MakePolygon('LINESTRING (0 0, 0 150, 150 150, 150 "
	//           "0, 0 0)', ['LINESTRING(20 20, 50 20, 50 50, 20 50, 20 20)'::GEOMETRY, 'LINESTRING (90 100, 90 80, 110 "
	//           "80, 110 100, 90 100)'::GEOMETRY]))");

	// auto create_rv = con.Query("CREATE TABLE geometries1 (g Geometry);");
	// create_rv->Print();
	// auto insert_rv = con.Query("INSERT INTO geometries1 VALUES('{\"type\":\"MultiPolygon\",\"coordinates\":[[[[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,32],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,32],[-117,32],[-117,32],[-117,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-116,32],[-117,32],[-117,32],[-117,32],[-117,32]],[[-117,33],[-117,33],[-117,33],[-117,33],[-117,33],[-117,32],[-117,33]]]]}'), ('{\"type\":\"MultiPolygon\",\"coordinates\":[[[[4,0],[0,-4],[-4,0],[0,4],[4,0]],[[2,0],[0,2],[-2,0],[0,-2],[2,0]]],[[[24,0],[20,-4],[16,0],[20,4],[24,0]],[[22,0],[20,2],[18,0],[20,-2],[22,0]]],[[[44,0],[40,-4],[36,0],[40,4],[44,0]],[[42,0],[40,2],[38,0],[40,-2],[42,0]]]]}')");
	// insert_rv->Print();
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

	// auto rv10 = con.Query("SELECT ST_AsText(ST_Difference(ST_GeomFromText('MULTIPOINT(-118.58 38.38 5,-118.60 38.329
	// 6,-118.614 38.281 7)'), ST_GeomFromText('POINT(-118.614 38.281 5)')));"); rv10->Print();

	// auto rv9 = con.Query("SELECT ST_ASTEXT(ST_EXTENT(['POINT(0 0)'::geometry, 'LINESTRING ( -2 2, 2 2 )'::geometry, 'GEOMETRYCOLLECTION(LINESTRING(0 0,1 1),LINESTRING(5 5,4 4),LINESTRING(0 0,-1 -1),POLYGON((0 0,4 0,4 4,0 4,0 0)))'::geometry, 'MULTIPOLYGON(((743238 2967416,743238 2967450,743265 2967450,743265.625 2967416,743238 2967416)))']));");
	// // auto rv9 = con.Query("SELECT ST_ASTEXT(ST_BOUNDINGBOX('GEOMETRYCOLLECTION(POINT(0 0),LINESTRING(-2 2,2 2))'::geometry));");
	// rv9->Print();

	// auto rv10 = con.Query("SELECT ST_MaxDistance('POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))', 'POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))');");
	// rv10->Print();

	// auto rv11 = con.Query("SELECT ST_Distance('POINT(10 30)', 'POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))', true);");
	// rv11->Print();

	// auto rv12 = con.Query("SELECT ST_Distance('POINT(30 30)', 'POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))', true);");
	// rv12->Print();

	// auto rv13 = con.Query("SELECT ST_Distance('POINT(30 10)', 'POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))', true);");
	// rv13->Print();

	// auto rv14 = con.Query("SELECT ST_Distance('POLYGON (( 10 30, 30 30, 30 10, 10 10, 10 30))', 'POINT(-21.96 64.15)', true);");
	// rv14->Print();

	// auto rv10 = con.Query("SELECT ST_AsText(ST_ClosestPoint('LINESTRING (20 80, 98 190, 110 180, 50 75 )', 'POINT(100
	// 100)'));"); rv10->Print();

	// auto create_win_rv = con.Query("CREATE TABLE dbscan_inputs (id int, geom geometry);");
	// create_win_rv->Print();

	// // auto insert_win_rv = con.Query("INSERT INTO dbscan_inputs VALUES (0, 'POINT EMPTY'),(1, 'POINT (0 0)'),(2, 'POINT (1 1)'),(3, 'POINT (-0.5 0.5)'),(4, 'POINT (1 0)'),(5, 'POINT (0 1)'),(6, 'POINT (1.0 0.5)');");
	// // auto insert_win_rv = con.Query("INSERT INTO dbscan_inputs VALUES (1, 'POINT EMPTY'),(2, 'MULTIPOINT(1 1, 2 2, 4 4, 5 2)'),(3, 'POINT(14 15)'),(4, 'LINESTRING(40 1, 42 34, 44 39)'),(5, 'POLYGON((40 2, 40 1, 41 2, 40 2))');");
	// auto insert_win_rv = con.Query("INSERT INTO dbscan_inputs VALUES (1, 'LINESTRING (0 0, 1 1)'),(2, 'LINESTRING (5 5, 4 4)'),(3, 'LINESTRING (6 6, 7 7)'),(4, 'LINESTRING (0 0, -1 -1)'),(5, 'POLYGON ((0 0, 4 0, 4 4, 0 4, 0 0))');");
	// insert_win_rv->Print();

	// auto select_rv = con.Query("SELECT id, ST_ASTEXT(geom) from dbscan_inputs");
	// select_rv->Print();

	// auto win_rv = con.Query("select id, ST_CLUSTERDBSCAN(geom, 0.6, 1) over (order by id desc rows between 3 preceding and current row) as m from dbscan_inputs;");
	// auto win_rv = con.Query("select id, ST_ASTEXT(geom) as geom_text, ST_CLUSTERDBSCAN(geom, 1e5, 1) over () as m from dbscan_inputs;");
	// win_rv->Print();

	// auto win2_rv = con.Query("select ST_ClusterDBSCAN(foo1.the_geom, 20.1, 1) OVER()  As result FROM ((SELECT geom  As the_geom FROM (VALUES ( ST_GEOMFROMTEXT('SRID=4326;POLYGONM((-71.1319 42.2503 1,-71.132 42.2502 3,-71.1323 42.2504 -2,-71.1322 42.2505 1,-71.1319 42.2503 0))') ), ( ST_GEOMFROMTEXT('SRID=4326;POLYGONM((-71.1319 42.2512 0,-71.1318 42.2511 20,-71.1317 42.2511 -20,-71.1317 42.251 5,-71.1317 42.2509 4,-71.132 42.2511 6,-71.1319 42.2512 30))') ) ) As g(geom))) As foo1 LIMIT 3;");
	// win2_rv->Print();

	// auto win3_rv = con.Query("SELECT ST_ClusterDBSCAN(ST_MAKEPOINT(1,1), 20.1, 5) OVER();");
	// win3_rv->Print();

	// auto win4_rv = con.Query("select ST_ASTEXT(geom) as geom, ST_ClusterKMeans(geom,3) over () as cid from (values ('LINESTRING(5 1, 2 0)'),('LINESTRING(0 0, 0 0)'::geometry), ('POINT(2 6)'), ('POINT(1 1)'), ('POINT(1 5)'), ('POINT(2 2)')) g(geom);");
	// win4_rv->Print();

	// auto win5_rv = con.Query("select ST_ASTEXT(unnest(ST_ClusterWithin(ARRAY['SRID=4326;POINT (3 7)'::geometry, 'SRID=4326;LINESTRING (3 0, 3 9)'], 0)));");
	// win5_rv->Print();

	// auto win6_rv = con.Query("SELECT ST_MAKEPOLYGON('POINT(5 6)', ['a']);");
	// win6_rv->Print();

	auto geom = con.Query("SELECT ST_ASTEXT('aaa');");
	geom->Print();


	// auto rv1 = con.Query("CREATE TABLE geometries(g Geometry);");
	// rv1->Print();

	// auto rv2 = con.Query("INSERT INTO geometries VALUES('POINT(1 1)');");
	// rv2->Print();

	// auto rv3 = con.Query("select ST_ASBINARY(g)::VARCHAR from geometries;");
	// rv3->Print();

}
