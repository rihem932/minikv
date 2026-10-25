#pragma once

#include <string>

#include "kvstore.hpp"

// Runs one command line (e.g. "SET name Rihem") on the store
// and returns the text to print. Returns "" for an empty line.
std::string handle_command(KVStore& store, const std::string& line);
