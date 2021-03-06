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
#ifndef DOGEN_QUILT_CPP_TYPES_FABRIC_CMAKELISTS_HPP
#define DOGEN_QUILT_CPP_TYPES_FABRIC_CMAKELISTS_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif

#include <iosfwd>
#include <string>
#include <algorithm>
#include "dogen/yarn/types/element.hpp"
#include "dogen/quilt.cpp/serialization/fabric/cmakelists_fwd_ser.hpp"

namespace dogen {
namespace quilt {
namespace cpp {
namespace fabric {

class cmakelists final : public dogen::yarn::element {
public:
    cmakelists() = default;
    cmakelists(const cmakelists&) = default;
    cmakelists(cmakelists&&) = default;

    virtual ~cmakelists() noexcept { }

public:
    cmakelists(
        const std::string& documentation,
        const dogen::annotations::annotation& annotation,
        const dogen::yarn::name& name,
        const dogen::yarn::origin_types origin_type,
        const boost::optional<dogen::yarn::name>& contained_by,
        const bool in_global_module,
        const std::vector<std::string>& stereotypes,
        const bool is_element_extension,
        const std::string& include_directory_path,
        const std::string& source_directory_name,
        const std::string& odb_include_directory_path,
        const std::string& odb_inclusion_directory_path,
        const std::string& odb_source_directory_path,
        const std::string& odb_options_file_path,
        const std::string& odb_postfix,
        const std::string& types_include_directory_path,
        const std::string& header_file_extension,
        const std::string& implementation_file_extension);

private:
    template<typename Archive>
    friend void boost::serialization::save(Archive& ar, const dogen::quilt::cpp::fabric::cmakelists& v, unsigned int version);

    template<typename Archive>
    friend void boost::serialization::load(Archive& ar, dogen::quilt::cpp::fabric::cmakelists& v, unsigned int version);

public:
    using dogen::yarn::element::accept;

    virtual void accept(const dogen::yarn::element_visitor& v) const override;
    virtual void accept(dogen::yarn::element_visitor& v) const override;
    virtual void accept(const dogen::yarn::element_visitor& v) override;
    virtual void accept(dogen::yarn::element_visitor& v) override;
public:
    void to_stream(std::ostream& s) const override;

public:
    const std::string& include_directory_path() const;
    std::string& include_directory_path();
    void include_directory_path(const std::string& v);
    void include_directory_path(const std::string&& v);

    const std::string& source_directory_name() const;
    std::string& source_directory_name();
    void source_directory_name(const std::string& v);
    void source_directory_name(const std::string&& v);

    const std::string& odb_include_directory_path() const;
    std::string& odb_include_directory_path();
    void odb_include_directory_path(const std::string& v);
    void odb_include_directory_path(const std::string&& v);

    const std::string& odb_inclusion_directory_path() const;
    std::string& odb_inclusion_directory_path();
    void odb_inclusion_directory_path(const std::string& v);
    void odb_inclusion_directory_path(const std::string&& v);

    const std::string& odb_source_directory_path() const;
    std::string& odb_source_directory_path();
    void odb_source_directory_path(const std::string& v);
    void odb_source_directory_path(const std::string&& v);

    const std::string& odb_options_file_path() const;
    std::string& odb_options_file_path();
    void odb_options_file_path(const std::string& v);
    void odb_options_file_path(const std::string&& v);

    const std::string& odb_postfix() const;
    std::string& odb_postfix();
    void odb_postfix(const std::string& v);
    void odb_postfix(const std::string&& v);

    const std::string& types_include_directory_path() const;
    std::string& types_include_directory_path();
    void types_include_directory_path(const std::string& v);
    void types_include_directory_path(const std::string&& v);

    const std::string& header_file_extension() const;
    std::string& header_file_extension();
    void header_file_extension(const std::string& v);
    void header_file_extension(const std::string&& v);

    const std::string& implementation_file_extension() const;
    std::string& implementation_file_extension();
    void implementation_file_extension(const std::string& v);
    void implementation_file_extension(const std::string&& v);

public:
    bool operator==(const cmakelists& rhs) const;
    bool operator!=(const cmakelists& rhs) const {
        return !this->operator==(rhs);
    }

public:
    bool equals(const dogen::yarn::element& other) const override;

public:
    void swap(cmakelists& other) noexcept;
    cmakelists& operator=(cmakelists other);

private:
    std::string include_directory_path_;
    std::string source_directory_name_;
    std::string odb_include_directory_path_;
    std::string odb_inclusion_directory_path_;
    std::string odb_source_directory_path_;
    std::string odb_options_file_path_;
    std::string odb_postfix_;
    std::string types_include_directory_path_;
    std::string header_file_extension_;
    std::string implementation_file_extension_;
};

} } } }

namespace std {

template<>
inline void swap(
    dogen::quilt::cpp::fabric::cmakelists& lhs,
    dogen::quilt::cpp::fabric::cmakelists& rhs) {
    lhs.swap(rhs);
}

}

#endif
