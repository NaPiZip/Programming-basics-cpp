// Copyright 2019, Nawin

#ifndef _HEADER_WORKSPACE
#define _HEADER_WORKSPACE


struct Database {
protected:
  Database() {}

public:
  static Database& get();
  Database(const Database&) = delete;
  Database(Database&&) = delete;
  Database& operator=(const Database&) = delete;
  Database& operator=(Database&&) = delete;
};
#endif // _HEADER_WORKSPACE
