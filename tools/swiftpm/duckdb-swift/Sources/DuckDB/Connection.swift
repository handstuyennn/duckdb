//
//  DuckDB
//  https://github.com/duckdb/duckdb-swift
//
//  Copyright © 2018-2023 Stichting DuckDB Foundation
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.

@_implementationOnly import Cduckdb

public final class Connection {

  private let database: Database
  private let ptr = UnsafeMutablePointer<duckdb_connection?>.allocate(capacity: 1)

  public init(database: Database) throws {
    self.database = database
    let status = database.withCDatabase { duckdb_connect($0, ptr) }
    guard status == .success else { throw DatabaseError.connectionFailedToInitialize }
  }

  deinit {
    duckdb_disconnect(ptr)
    ptr.deallocate()
  }
  
  public func query(_ sql: String) throws -> QueryResult {
    try QueryResult(connection: self, sql: sql)
  }
  
  public func execute(_ sql: String) throws {
    let status = sql.withCString { queryStrPtr in
      duckdb_query(ptr.pointee, queryStrPtr, nil)
    }
    guard status == .success else {
      throw DatabaseError.connectionQueryError(reason: nil)
    }
  }
  
  func withCConnection<T>(_ body: (duckdb_connection?) throws -> T) rethrows -> T {
    try body(ptr.pointee)
  }
}
