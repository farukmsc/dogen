/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2012 Kitanda <info@kitanda.co.uk>
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
#include <iostream>
#include <ostream>
#include "dogen/cpp/types/formatters/doxygen_comments.hpp"
#include "dogen/cpp/types/formatters/qualified_name.hpp"
#include "dogen/cpp/types/formatters/class_declaration.hpp"

namespace dogen {
namespace cpp {
namespace formatters {

class_declaration::
class_declaration(std::ostream& stream, const bool disable_serialization)
    : stream_(stream), utility_(stream_, indenter_),
      disable_serialization_(disable_serialization) { }

void class_declaration::open_class(const class_view_model& vm) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(vm.documentation());
    stream_ << indenter_ << "class " << vm.name();

    if (!vm.is_parent())
        stream_ << " final";

    const auto parents(vm.parents());
    if (!parents.empty()) {
        stream_ << " :";

        qualified_name qualified_name(stream_);
        if (parents.size() == 1) {
            stream_ << " public ";
            qualified_name.format(parents.front());
        } else {
            bool is_first(true);
            positive_indenter_scope s(indenter_);
            for (const auto p : vm.parents()) {
                stream_ << (is_first ? "" : ",") << std::endl << indenter_;
                stream_ << " public " << p.name();
                is_first = false;
            }
        }
    }
    stream_ << " {" << std::endl;
}

void class_declaration::close_class() {
    stream_ << indenter_ << "};" << std::endl;
    utility_.blank_line();
}

void class_declaration::default_constructor(const class_view_model& vm) {
    if (!vm.requires_manual_default_constructor())
        return;

    const auto props(vm.properties());
    utility_.public_access_specifier();
    stream_ << indenter_ << vm.name() << "();" << std::endl;
    utility_.blank_line();
}

void class_declaration::complete_constructor(const class_view_model& vm) {
    const auto props(vm.all_properties());
    if (props.empty())
        return;

    utility_.public_access_specifier();
    if (props.size() == 1) {
        const auto p(*props.begin());
        stream_ << indenter_ << "explicit " << vm.name() << "(const "
                << p.type().complete_name();

        if (!p.type().is_primitive())
            stream_ << "&";

        stream_ << " " << p.name() << ");" << std::endl;
        utility_.blank_line();
        return;
    }

    stream_ << indenter_ << vm.name() << "(";
    {
        positive_indenter_scope s(indenter_);
        bool is_first(true);
        for (const auto p : props) {
            stream_ << (is_first ? "" : ",") << std::endl;
            stream_ << indenter_ << "const " << p.type().complete_name();

            if (!p.type().is_primitive())
                stream_ << "&";

            stream_ << " " << p.name();
            is_first = false;
        }
        stream_ << ");" << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::move_constructor(const class_view_model& vm) {
    if (!vm.requires_manual_move_constructor())
        return;

    const auto props(vm.all_properties());
    if (props.empty())
        return;

    utility_.public_access_specifier();
    const auto p(*props.begin());
    stream_ << indenter_ << vm.name() << "(" << vm.name()
            << "&& rhs);" << std::endl;
    utility_.blank_line();
}

void class_declaration::destructor(const class_view_model& vm) {
    /*
     * according to MEC++, item 33, base classes should always be
     * abstract. this avoids all sorts of tricky problems with
     * assignment and swap.
     *
     * incidentally, this also fixes some strange clang errors:
     * undefined reference to `vtable.
     */
    if (vm.is_parent()) {
        stream_ << indenter_ << "virtual ~" << vm.name()
                << "() noexcept = 0;" << std::endl;
        utility_.blank_line();
    }
}

void class_declaration::
compiler_generated_constuctors(const class_view_model& vm) {
    utility_.public_access_specifier();

    if (!vm.requires_manual_default_constructor())
        stream_ << indenter_ << vm.name() << "() = default;" << std::endl;

    stream_ << indenter_ << vm.name() << "(const " << vm.name()
            << "&) = default;" << std::endl;

    if (!vm.requires_manual_move_constructor()) {
        stream_ << indenter_ << vm.name() << "(" << vm.name() << "&&) = default;"
                << std::endl;
    }

    if (!vm.is_parent() && vm.parents().empty()) {
        stream_ << indenter_ << "~" << vm.name() << "() = default;"
                << std::endl;
    }

    if (vm.all_properties().empty()) {
        stream_ << indenter_ << vm.name() << "& operator=(const " << vm.name()
                << "&) = default;" << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::friends(const class_view_model& vm) {
    if (disable_serialization_)
        return;

    utility_.private_access_specifier();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "friend void boost::serialization::save(Archive& ar"
            << ", const " << vm.name() << "& v, unsigned int version);"
            << std::endl;
    utility_.blank_line();

    stream_ << indenter_ << "template<typename Archive>" << std::endl
            << indenter_ << "friend void boost::serialization::load(Archive& ar"
            << ", " << vm.name() << "& v, unsigned int version);" << std::endl;
    utility_.blank_line();
}

void class_declaration::
non_pod_getters_and_setters(const property_view_model& vm) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(vm.documentation());
    dc.format_start_block(vm.documentation());
    stream_ << indenter_ << vm.type().complete_name() << " " << vm.name()
            << "() const;" << std::endl;

    stream_ << indenter_ << "void " << vm.name() << "(const "
            << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&";

    stream_ << " v);" << std::endl;
    dc.format_end_block(vm.documentation());
    utility_.blank_line();
}

void class_declaration::
pod_getters_and_setters(const property_view_model& vm) {
    doxygen_comments dc(stream_, indenter_);
    dc.format(vm.documentation());
    dc.format_start_block(vm.documentation());

    // const getter
    stream_ << indenter_ << "const " << vm.type().complete_name()
            << "& " << vm.name()
            << "() const;" << std::endl;

    // Popsicle immutability
    stream_ << indenter_ << "" << vm.type().complete_name()
            << "& " << vm.name()
            << "();" << std::endl;

    // traditional setter
    stream_ << indenter_ << "void " << vm.name() << "(const "
            << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&";

    stream_ << " v);" << std::endl;

    // move setter
    stream_ << indenter_ << "void " << vm.name() << "(const "
            << vm.type().complete_name();

    if (!vm.type().is_primitive())
        stream_ << "&&";

    stream_ << " v);" << std::endl;

    dc.format_end_block(vm.documentation());
    utility_.blank_line();
}

void class_declaration::getters_and_setters(const class_view_model& vm) {
    if (vm.properties().empty())
        return;

    utility_.public_access_specifier();
    for (const auto p : vm.properties()) {
        if (p.type().is_primitive() || p.type().is_enumeration()) {
            non_pod_getters_and_setters(p);
            continue;
        }

        pod_getters_and_setters(p);
    }
}

void class_declaration::member_variables(const class_view_model& vm) {
    if (vm.properties().empty())
        return;

    utility_.private_access_specifier();
    for (const auto p : vm.properties()) {
        stream_ << indenter_ << p.type().complete_name() << " "
                << utility_.as_member_variable(p.name()) << ";"
                << std::endl;
    }
}

void class_declaration::equality(const class_view_model& vm) {
    // equality is only public in leaf classes - MEC++-33
    if (vm.is_parent()) {
        utility_.protected_access_specifier();
        stream_ << indenter_ << "bool compare(const " << vm.name()
                <<  "& rhs) const;" << std::endl;
    } else {
        utility_.public_access_specifier();

        stream_ << indenter_ << "bool operator==(const " << vm.name()
                <<  "& rhs) const;" << std::endl;
        stream_ << indenter_ << "bool operator!=(const " << vm.name()
                << "& rhs) const ";
        utility_.open_scope();
        {
            positive_indenter_scope s(indenter_);
            stream_ << indenter_ << "return !this->operator==(rhs);" << std::endl;
        }
        utility_.close_scope();
        utility_.blank_line();
    }

    if (!vm.is_parent() && vm.parents().empty())
        return;

    utility_.public_access_specifier();
    if (vm.is_parent() && vm.parents().empty()) {
        stream_ << indenter_
                << "virtual bool equals(const " << vm.name()
                <<  "& other) const = 0;"
                << std::endl;
    } else if (vm.is_parent()) {
        stream_ << indenter_
                << "virtual bool equals(const " << vm.original_parent_name()
                <<  "& other) const = 0;"
                << std::endl;
    } else {
        stream_ << indenter_
                << "bool equals(const " << vm.original_parent_name()
                <<  "& other) const override;"
                << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::to_stream(const class_view_model& vm) {
    if (!vm.is_parent() && vm.parents().empty())
        return;

    utility_.public_access_specifier();
    if (vm.is_parent()) {
        stream_ << indenter_
                << "virtual void to_stream("
                << "std::ostream& s) const;"
                << std::endl;
    } else {
        stream_ << indenter_
                << "void to_stream(std::ostream& s) "
                << "const override;"
                << std::endl;
    }
    utility_.blank_line();
}

void class_declaration::swap_and_assignment(const class_view_model& vm) {
    if (vm.all_properties().empty() && !vm.is_parent())
        return;

    // swap is only public in leaf classes - MEC++-33
    if (vm.is_parent())
        utility_.protected_access_specifier();
    else
        utility_.public_access_specifier();

    stream_ << indenter_ << "void swap(" << vm.name() << "& other) noexcept;"
            << std::endl;

    // assignment is only available in leaf classes - MEC++-33
    if (!vm.is_parent()) {
        stream_ << indenter_ << vm.name() << "& operator=(" << vm.name()
                << " other);" << std::endl;
    }

    utility_.blank_line();
}

} } }
