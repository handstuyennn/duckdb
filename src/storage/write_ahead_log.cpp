#include "duckdb/storage/write_ahead_log.hpp"

#include "duckdb/catalog/catalog_entry/scalar_macro_catalog_entry.hpp"
#include "duckdb/catalog/catalog_entry/schema_catalog_entry.hpp"
#include "duckdb/catalog/catalog_entry/table_catalog_entry.hpp"
#include "duckdb/catalog/catalog_entry/type_catalog_entry.hpp"
#include "duckdb/catalog/catalog_entry/view_catalog_entry.hpp"
#include "duckdb/main/database.hpp"
#include "duckdb/parser/parsed_data/alter_table_info.hpp"
#include <cstring>

namespace duckdb {

WriteAheadLog::WriteAheadLog(AttachedDatabase &database, const string &path) : skip_writing(false), database(database) {
	wal_path = path;
	writer = make_uniq<BufferedFileWriter>(FileSystem::Get(database), path.c_str(),
	                                       FileFlags::FILE_FLAGS_WRITE | FileFlags::FILE_FLAGS_FILE_CREATE |
	                                           FileFlags::FILE_FLAGS_APPEND);
}

WriteAheadLog::~WriteAheadLog() {
}

int64_t WriteAheadLog::GetWALSize() {
	D_ASSERT(writer);
	return writer->GetFileSize();
}

idx_t WriteAheadLog::GetTotalWritten() {
	D_ASSERT(writer);
	return writer->GetTotalWritten();
}

void WriteAheadLog::Truncate(int64_t size) {
	writer->Truncate(size);
}

void WriteAheadLog::Delete() {
	if (!writer) {
		return;
	}
	writer.reset();

	auto &fs = FileSystem::Get(database);
	fs.RemoveFile(wal_path);
}

//===--------------------------------------------------------------------===//
// Write Entries
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCheckpoint(block_id_t meta_block) {
	writer->Write<WALType>(WALType::CHECKPOINT);
	writer->Write<block_id_t>(meta_block);
}

//===--------------------------------------------------------------------===//
// CREATE TABLE
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateTable(const TableCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_TABLE);
	entry.Serialize(*writer);
}

//===--------------------------------------------------------------------===//
// DROP TABLE
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteDropTable(const TableCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_TABLE);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// CREATE SCHEMA
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateSchema(const SchemaCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_SCHEMA);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// SEQUENCES
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateSequence(const SequenceCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_SEQUENCE);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropSequence(const SequenceCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_SEQUENCE);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

void WriteAheadLog::WriteSequenceValue(const SequenceCatalogEntry &entry, SequenceValue val) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::SEQUENCE_VALUE);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
	writer->Write<uint64_t>(val.usage_count);
	writer->Write<int64_t>(val.counter);
}

//===--------------------------------------------------------------------===//
// MACROS
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateMacro(const ScalarMacroCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_MACRO);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropMacro(const ScalarMacroCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_MACRO);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

void WriteAheadLog::WriteCreateTableMacro(const TableMacroCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_TABLE_MACRO);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropTableMacro(const TableMacroCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_TABLE_MACRO);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// Indexes
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateIndex(const IndexCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_INDEX);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropIndex(const IndexCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_INDEX);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// Custom Types
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateType(const TypeCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_TYPE);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropType(const TypeCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_TYPE);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// VIEWS
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteCreateView(const ViewCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::CREATE_VIEW);
	entry.Serialize(*writer);
}

void WriteAheadLog::WriteDropView(const ViewCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_VIEW);
	writer->WriteString(entry.schema->name);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// DROP SCHEMA
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteDropSchema(const SchemaCatalogEntry &entry) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::DROP_SCHEMA);
	writer->WriteString(entry.name);
}

//===--------------------------------------------------------------------===//
// DATA
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteSetTable(string &schema, string &table) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::USE_TABLE);
	writer->WriteString(schema);
	writer->WriteString(table);
}

void WriteAheadLog::WriteInsert(DataChunk &chunk) {
	if (skip_writing) {
		return;
	}
	D_ASSERT(chunk.size() > 0);
	chunk.Verify();

	writer->Write<WALType>(WALType::INSERT_TUPLE);
	chunk.Serialize(*writer);
}

void WriteAheadLog::WriteDelete(DataChunk &chunk) {
	if (skip_writing) {
		return;
	}
	D_ASSERT(chunk.size() > 0);
	D_ASSERT(chunk.ColumnCount() == 1 && chunk.data[0].GetType() == LogicalType::ROW_TYPE);
	chunk.Verify();

	writer->Write<WALType>(WALType::DELETE_TUPLE);
	chunk.Serialize(*writer);
}

void WriteAheadLog::WriteUpdate(DataChunk &chunk, const vector<column_t> &column_indexes) {
	if (skip_writing) {
		return;
	}
	D_ASSERT(chunk.size() > 0);
	D_ASSERT(chunk.ColumnCount() == 2);
	D_ASSERT(chunk.data[1].GetType().id() == LogicalType::ROW_TYPE);
	chunk.Verify();

	writer->Write<WALType>(WALType::UPDATE_TUPLE);
	writer->Write<idx_t>(column_indexes.size());
	for (auto &col_idx : column_indexes) {
		writer->Write<column_t>(col_idx);
	}
	chunk.Serialize(*writer);
}

//===--------------------------------------------------------------------===//
// Write ALTER Statement
//===--------------------------------------------------------------------===//
void WriteAheadLog::WriteAlter(data_ptr_t ptr, idx_t data_size) {
	if (skip_writing) {
		return;
	}
	writer->Write<WALType>(WALType::ALTER_INFO);
	writer->WriteData(ptr, data_size);
}

//===--------------------------------------------------------------------===//
// FLUSH
//===--------------------------------------------------------------------===//
void WriteAheadLog::Flush() {
	if (skip_writing) {
		return;
	}
	// write an empty entry
	writer->Write<WALType>(WALType::WAL_FLUSH);
	// flushes all changes made to the WAL to disk
	writer->Sync();
}

} // namespace duckdb
