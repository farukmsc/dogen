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
#include "dogen/quilt.csharp/types/formatters/test_data/enum_formatter.hpp"
#include "dogen/quilt.csharp/types/formatters/assistant.hpp"
#include "dogen/quilt.csharp/types/formatters/test_data/traits.hpp"
#include "dogen/quilt.csharp/types/traits.hpp"
#include "dogen/formatters/types/sequence_formatter.hpp"
#include "dogen/yarn/types/enumeration.hpp"
#include <boost/make_shared.hpp>
#include <typeinfo>

namespace dogen {
namespace quilt {
namespace csharp {
namespace formatters {
namespace test_data {

std::string enum_formatter::static_artefact() {
    return traits::enum_archetype();
}

std::string enum_formatter::formatter_name() const {
    static auto r(archetype_location().archetype());
    return r;
}

annotations::archetype_location enum_formatter::archetype_location() const {
    static annotations::archetype_location
        r(csharp::traits::family(), csharp::traits::kernel(),
          traits::facet(),
          enum_formatter::static_artefact());
    return r;
}

std::type_index enum_formatter::element_type_index() const {
    static auto r(std::type_index(typeid(yarn::enumeration)));
    return r;
}

boost::filesystem::path enum_formatter::
full_path(const formattables::locator& l, const yarn::name& n) const {
    return l.make_full_path(n, static_artefact());
}

std::list<std::string> enum_formatter::
inclusion_dependencies(const yarn::element& /*e*/) const {
    std::list<std::string> r;
    return r;
}

dogen::formatters::artefact
enum_formatter::format(const context& ctx, const yarn::element& e) const {
    const auto id(e.name().id());
    assistant a(ctx, archetype_location(), id);
    const auto& ye(a.as<yarn::enumeration>(static_artefact(), e));
    {
        const auto sn(e.name().simple());
        auto sbf(a.make_scoped_boilerplate_formatter());
        {
a.stream() << "using System;" << std::endl;
a.stream() << "using System.Collections;" << std::endl;
a.stream() << "using System.Collections.Generic;" << std::endl;
a.stream() << std::endl;
            const auto ns(a.make_namespaces(e.name()));
            auto snf(a.make_scoped_namespace_formatter(ns));
a.stream() << "    /// <summary>" << std::endl;
a.stream() << "    /// Generates sequences of " << sn << "." << std::endl;
a.stream() << "    /// </summary>" << std::endl;
a.stream() << "    public static class " << sn << "SequenceGenerator" << std::endl;
a.stream() << "    {" << std::endl;
a.stream() << "        static internal " << sn << " Create(uint position)" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            var result = (" << sn << ")(position % " << ye.enumerators().size() << ");" << std::endl;
a.stream() << "            return result;" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerator" << std::endl;
a.stream() << "        private class " << sn << "Enumerator : IEnumerator, IEnumerator<" << sn << ">, IDisposable" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region Properties" << std::endl;
a.stream() << "            private uint _position;" << std::endl;
a.stream() << "            private " << sn << " _current;" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            private void PopulateCurrent()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _current = " << sn << "SequenceGenerator.Create(_position);" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IDisposable" << std::endl;
a.stream() << "            public void Dispose()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            #region IEnumerator implementation" << std::endl;
a.stream() << "            public bool MoveNext()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                ++_position;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "                return true;" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public void Reset()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                _position = 0;" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            public object Current {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            " << sn << " IEnumerator<" << sn << ">.Current" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                get" << std::endl;
a.stream() << "                {" << std::endl;
a.stream() << "                    return _current;" << std::endl;
a.stream() << "                }" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "            public " << sn << "Enumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                PopulateCurrent();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        #region Enumerable" << std::endl;
a.stream() << "        private class " << sn << "Enumerable : IEnumerable, IEnumerable<" << sn << ">" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            #region IEnumerable implementation" << std::endl;
a.stream() << "            public IEnumerator GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << std::endl;
a.stream() << "            IEnumerator<" << sn << "> IEnumerable<" << sn << ">.GetEnumerator()" << std::endl;
a.stream() << "            {" << std::endl;
a.stream() << "                return new " << sn << "Enumerator();" << std::endl;
a.stream() << "            }" << std::endl;
a.stream() << "            #endregion" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "        #endregion" << std::endl;
a.stream() << std::endl;
a.stream() << "        static public IEnumerable<" << sn << "> Sequence()" << std::endl;
a.stream() << "        {" << std::endl;
a.stream() << "            return new " << sn << "Enumerable();" << std::endl;
a.stream() << "        }" << std::endl;
a.stream() << "    }" << std::endl;
        }
    } // sbf
    return a.make_artefact();
}
} } } } }
