/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
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
#include <ostream>
#include <boost/io/ios_state.hpp>
#include <boost/algorithm/string.hpp>
#include "dogen/options/io/knitting_options_io.hpp"

inline std::string tidy_up_string(std::string s) {
    boost::replace_all(s, "\r\n", "<new_line>");
    boost::replace_all(s, "\n", "<new_line>");
    boost::replace_all(s, "\"", "<quote>");
    boost::replace_all(s, "\\", "<backslash>");
    return s;
}

namespace std {

inline std::ostream& operator<<(std::ostream& s, const std::vector<std::string>& v) {
    s << "[ ";
    for (auto i(v.begin()); i != v.end(); ++i) {
        if (i != v.begin()) s << ", ";
        s << "\"" << tidy_up_string(*i) << "\"";
    }
    s << "] ";
    return s;
}

}

namespace dogen {
namespace options {

std::ostream& operator<<(std::ostream& s, const knitting_options& v) {
    boost::io::ios_flags_saver ifs(s);
    s.setf(std::ios_base::boolalpha);
    s.setf(std::ios::fixed, std::ios::floatfield);
    s.precision(6);
    s.setf(std::ios::showpoint);

    s << " { "
      << "\"__type__\": " << "\"dogen::options::knitting_options\"" << ", "
      << "\"log_level\": " << "\"" << tidy_up_string(v.log_level()) << "\"" << ", "
      << "\"target\": " << "\"" << v.target().generic_string() << "\"" << ", "
      << "\"delete_extra_files\": " << v.delete_extra_files() << ", "
      << "\"force_write\": " << v.force_write() << ", "
      << "\"ignore_patterns\": " << v.ignore_patterns() << ", "
      << "\"output_directory_path\": " << "\"" << v.output_directory_path().generic_string() << "\"" << ", "
      << "\"cpp_headers_output_directory_path\": " << "\"" << v.cpp_headers_output_directory_path().generic_string() << "\"" << ", "
      << "\"log_directory\": " << "\"" << v.log_directory().generic_string() << "\""
      << " }";
    return(s);
}

} }
