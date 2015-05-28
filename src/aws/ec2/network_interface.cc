/*
** Copyright 2011-2014 Merethis
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

#include "com/centreon/process.hh"
#include "com/centreon/aws/ec2/network_interface.hh"
#include "com/centreon/exceptions/basic.hh"

using namespace com::centreon::aws::ec2;

/**
 *  Default constructor.
 */
network_interface::network_interface()
  : _device_index(0),
    _delete_on_termination(false),
    _associate_ip_address(true) {

}
/**
 *  Copy constructor.
 *
 *  @param[in] other  Object to copy.
 */
network_interface::network_interface(
  network_interface const& other) {
  _internal_copy(other);
}

/**
 *  Assignment operator.
 *
 *  @param[in] other  Object to copy.
 *
 *  @return           Reference to this object.
 */
network_interface& network_interface::operator=(
                     network_interface const& other) {
  if (this != &other)
    _internal_copy(other);
  return (*this);
}

/**
 *  Destructor.
 */
network_interface::~network_interface() {

}

/**
 *  Copy an object.
 *
 *  @param other  Object to copy.
 */
void network_interface::_internal_copy(network_interface const& other) {
  _network_interface_id = other._network_interface_id;
  _device_index = other._device_index;
  _subnet_id = other._subnet_id;
  _description = other._description;
  _private_ip_address = other._private_ip_address;
  _groups = other._groups;
  _delete_on_termination = other._delete_on_termination;
  _private_ip_addresses = other._private_ip_addresses;
  _secondary_private_ip_address_count = other._secondary_private_ip_address_count;
  _associate_ip_address = other._associate_ip_address;
}
