/*
** Copyright 2011-2013 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#ifndef CC_HANDLE_LISTENER_HH
#  define CC_HANDLE_LISTENER_HH

#  include "com/centreon/namespace.hh"
#  include "com/centreon/handle.hh"

CC_BEGIN()

/**
 *  @class handle_listener handle_listener.hh "com/centreon/handle_listener.hh"
 *  @brief Base for all handle_listener objects.
 *
 *  This class is an interface to receive notification from
 *  handle_manager for specific handle.
 */
class          handle_listener {
public:
               handle_listener();
  virtual      ~handle_listener() throw ();
  virtual void error(handle& h) = 0;
  virtual void read(handle& h);
  virtual bool want_read(handle& h);
  virtual bool want_write(handle& h);
  virtual void write(handle& h);
};

CC_END()

#endif // !CC_HANDLE_LISTENER_HH
