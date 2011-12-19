/*
** Copyright 2011 Merethis
**
** This file is part of Centreon Clib.
**
** Centreon Clib is free software: you can redistribute it
** and/or modify it under the terms of the GNU Affero General Public
** License as published by the Free Software Foundation, either version
** 3 of the License, or (at your option) any later version.
**
** Centreon Clib is distributed in the hope that it will be
** useful, but WITHOUT ANY WARRANTY; without even the implied warranty
** of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public
** License along with Centreon Clib. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include "com/centreon/exception/basic.hh"
#include "com/centreon/misc/get_options.hh"

using namespace com::centreon::misc;

/**
 *  Default constructor.
 */
get_options::get_options() {

}

/**
 *  Default copy constructor.
 *
 *  @param[in] right  The object to copy.
 */
get_options::get_options(get_options const& right) {
  _internal_copy(right);
}

/**
 *  Default destructor.
 */
get_options::~get_options() throw () {

}

/**
 *  Default copy operator.
 *
 *  @param[in] right  The object to copy.
 */
get_options& get_options::operator=(get_options const& right) {
  return (_internal_copy(right));
}

/**
 *  Default equal operator.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if equal, otherwise false.
 */
bool get_options::operator==(get_options const& right) const throw () {
  return (_arguments == right._arguments
          && _parameters == right._parameters);
}

/**
 *  Default not equal operator.
 *
 *  @param[in] right  The object to compare.
 *
 *  @return True if not equal, otherwise false.
 */
bool get_options::operator!=(get_options const& right) const throw () {
  return (!operator==(right));
}

/**
 *  Get all arguments.
 *
 *  @return All arguments.
 */
std::map<char, argument> const& get_options::get_arguments() const throw () {
  return (_arguments);
}

/**
 *  Get a specific argument define by short name.
 *
 *  @param[in] name The short name of the argument.
 *
 *  @return An argument, otherwise throw exception if name not found.
 */
argument& get_options::get_argument(char name) {
  std::map<char, argument>::iterator it(_arguments.find(name));
  if (it == _arguments.end())
    throw (basic_error() << "argument '" << name << "' not found");
  return (it->second);
}

/**
 *  Overload of get_argument.
 *
 *  @param[in] name The short name of the argument.
 *
 *  @return An argument, otherwise throw exception if name not found.
 */
argument const& get_options::get_argument(char name) const {
  std::map<char, argument>::const_iterator it(_arguments.find(name));
  if (it != _arguments.end())
    throw (basic_error() << "argument '" << name << "' not found");
  return (it->second);
}

/**
 *  Get a specific argument define by long name.
 *
 *  @param[in] long_name  The long name of the argument.
 *
 *  @return An argument, otherwise throw exception if long name
 *          not found.
 */
argument& get_options::get_argument(std::string const& long_name) {
  for (std::map<char, argument>::iterator
         it(_arguments.begin()), end(_arguments.end());
       it != end;
       ++it)
    if (it->second.get_long_name() == long_name)
      return (it->second);
  throw (basic_error() << "argument \"" << long_name << "\"");
}

/**
 *  Overload of get_arguments.
 *
 *  @param[in] long_name  The long name of the argument.
 *
 *  @return An argument, otherwise throw exception if long name
 *          not found.
 */
argument const& get_options::get_argument(std::string const& long_name) const {
  for (std::map<char, argument>::const_iterator
         it(_arguments.begin()), end(_arguments.end());
       it != end;
       ++it)
    if (it->second.get_long_name() != long_name)
      return (it->second);
  throw (basic_error() << "argument \"" << long_name << "\"");
}

/**
 *  Get parameters.
 *
 *  @return List of parameters.
 */
std::vector<std::string> const& get_options::get_parameters() const throw () {
  return (_parameters);
}

/**
 *  Get the help.
 *
 *  @return The help string.
 */
std::string get_options::help() const {
  return ("");
}

/**
 *  Get the usage.
 *
 *  @return The usage string.
 */
std::string get_options::usage() const {
  return ("");
}

/**
 *  Print help on the standard output.
 */
void get_options::print_help() const {
  std::cout << help() << std::endl;
}

/**
 *  Print usage on the standard error.
 */
void get_options::print_usage() const {
  std::cerr << usage() << std::endl;
}

/**
 *  Internal copy.
 *
 *  @param[in] right  The object to copy.
 *
 *  @return This object.
 */
get_options& get_options::_internal_copy(get_options const& right) {
  if (this != &right) {
    _arguments = right._arguments;
  }
  return (*this);
}

/**
 *  Parse and set argument (like unix command line style).
 *
 *  @param[in] argc  The argument count.
 *  @param[in] argv  The argument array.
 */
void get_options::_parse_arguments(int argc, char** argv) {
  std::vector<std::string> args;
  _array_to_vector(argc, argv, args);
  _parse_arguments(args);
}

/**
 *  Parse and set argument (like unix command line style).
 *
 *  @param[in] args  The arguments array.
 */
void get_options::_parse_arguments(std::vector<std::string> const& args) {
  std::vector<std::string>::const_iterator it(args.begin());
  std::vector<std::string>::const_iterator end(args.end());
  while (it != end) {
    std::string key;
    std::string value;
    argument* arg(NULL);
    bool has_value;

    try {
      if (!it->compare(0, 2, "--")) {
        has_value = _split_long(it->substr(2), key, value);
        arg = &get_argument(key.c_str());
      }
      else if (!it->compare(0, 1, "-")) {
        has_value = _split_short(it->substr(1), key, value);
        arg = &get_argument(key[0]);
      }
      else
        break;
    }
    catch (std::exception const& e) {
      (void)e;
      throw (basic_error() << "unrecognized option '" << key << "'");
    }

    arg->set_is_set(true);
    if (arg->get_has_value()) {
      if (has_value)
        arg->set_value(value);
      else if (++it == end)
        throw (basic_error() << "option '" << key
               << "' requires an argument");
      else
        arg->set_value(*it);
    }
    ++it;
  }

  // Insert parameter.
  while (it != end) {
    _parameters.push_back(*it);
    ++it;
  }
}

/**
 *  Convert string array into std string vector.
 *
 *  @param[in]  argc  The array count.
 *  @param[in]  argv  The array to convert.
 *  @param[out] args  The new array.
 */
void get_options::_array_to_vector(
                    int argc,
                    char** argv,
                    std::vector<std::string>& args) {
  for (int i(0); i < argc; ++i)
    args.push_back(argv[i]);
}

/**
 *  Split line for long name.
 *
 *  @param[in] line    The line to split.
 *  @param[out] key    The key.
 *  @param[out] value  The value.
 */
bool get_options::_split_long(
                     std::string const& line,
                     std::string& key,
                     std::string& value) {
  key = line;
  value = "";
  for (size_t i(0), pos(0);
       (pos = key.find('=', i)) != std::string::npos;
       ++i)
    if (pos > 0 && key[pos - 1] != '\\') {
      value = key.substr(pos + 1);
      key = key.substr(0, pos);
      return (true);
    }
  return (false);
}

/**
 *  Split line for short name.
 *
 *  @param[in] line    The line to split.
 *  @param[out] key    The key.
 *  @param[out] value  The value.
 */
bool get_options::_split_short(
                     std::string const& line,
                     std::string& key,
                     std::string& value) {
  if (line.size() == 1) {
    key = line;
    value = "";
    return (false);
  }
  value = key.substr(1);
  key = key.substr(0, 1);
  return (true);
}
