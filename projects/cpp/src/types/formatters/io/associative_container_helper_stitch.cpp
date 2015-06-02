/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright(C) 2012 Kitanda <info@kitanda.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */
#include "dogen/cpp/types/formatters/io/associative_container_helper_stitch.hpp"
#include "dogen/formatters/types/cpp/scoped_namespace_formatter.hpp"

namespace dogen {
namespace cpp {
namespace formatters {
namespace io {

void associative_container_helper(std::ostream& s,
    const formattables::nested_type_info& t) {
    // using dogen::formatters::cpp::scoped_namespace_formatter;
    // scoped_namespace_formatter nsh(s, t.namespaces());
s << "inline std::ostream& operator<<(std::ostream& s, const " << t.complete_name() << "& v) {" << std::endl;
s << "    s << \'[\';" << std::endl;
s << "    for (auto i(v.begin()); i != v.end(); ++i) {" << std::endl;
s << "        if (i != v.begin()) s << \', \';" << std::endl;
s << "        s << \'__type__\'" << std::endl;
s << "    }" << std::endl;
s << std::endl;
s << std::endl;
s << std::endl;
s << "inline std::string tidy_up_string(std::string s) {" << std::endl;
s << "    boost::replace_all(s, \'\r\n\', \'<new_line>\');" << std::endl;
s << "    boost::replace_all(s, \'\n\', \'<new_line>\');" << std::endl;
s << "    boost::replace_all(s, \'\\'\', \'<quote>\');" << std::endl;
s << "    return s;" << std::endl;
s << "}" << std::endl;
}
} } } }