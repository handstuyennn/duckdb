#include "postgis/lwgeom_export.hpp"

#include "liblwgeom/gserialized.hpp"

namespace duckdb {

lwvarlena_t *LWGEOM_asGeoJson(GSERIALIZED *geom, size_t m_dec_digits) {
	LWGEOM *lwgeom;
	int precision = m_dec_digits;
	int output_bbox = LW_FALSE;
	int output_long_crs = LW_FALSE;
	int output_short_crs = LW_FALSE;
	int output_guess_short_srid = LW_FALSE;
	const char *srs = NULL;
	int32_t srid;

	srid = gserialized_get_srid(geom);

	lwgeom = lwgeom_from_gserialized(geom);
	auto geojson = lwgeom_to_geojson(lwgeom, srs, precision, output_bbox);
    lwgeom_free(lwgeom);
    return geojson;
}

} // namespace duckdb
