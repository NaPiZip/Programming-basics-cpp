// Copyright 2019, Nawin

#include "Workspace.h"


Database& Database::get() 
{
  static Database db;
  return db;
}