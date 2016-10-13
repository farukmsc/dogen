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
#include <unordered_set>
#include <boost/throw_exception.hpp>
#include "dogen/utility/log/logger.hpp"
#include "dogen/utility/io/set_io.hpp"
#include "dogen/utility/filesystem/file.hpp"
#include "dogen/utility/io/vector_io.hpp"
#include "dogen/utility/io/forward_list_io.hpp"
#include "dogen/annotations/io/type_repository_io.hpp"
#include "dogen/annotations/io/ownership_hierarchy_io.hpp"
#include "dogen/annotations/types/template_instantiator.hpp"
#include "dogen/annotations/types/building_error.hpp"
#include "dogen/annotations/types/type_templates_hydrator.hpp"
#include "dogen/annotations/types/type_repository_factory.hpp"

namespace {

using namespace dogen::utility::log;
static logger lg(logger_factory("annotations.type_repository_factory"));

const std::string annotations_dir("annotations");

const std::string duplicate_qualified_name(
    "Qualified name defined more than once: ");

}

namespace dogen {
namespace annotations {

std::list<type_template> type_repository_factory::hydrate_templates(
    const std::vector<boost::filesystem::path>& data_dirs) const {
    BOOST_LOG_SEV(lg, info) << "Input data directories: " << data_dirs;
    std::vector<boost::filesystem::path> annotation_dirs;
    annotation_dirs.reserve(data_dirs.size());
    for (const auto& dir : data_dirs)
        annotation_dirs.push_back(dir / annotations_dir);

    BOOST_LOG_SEV(lg, info) << "Finding all files in: " << annotation_dirs;
    const auto files(dogen::utility::filesystem::find_files(annotation_dirs));
    BOOST_LOG_SEV(lg, info) << "Files found: " << files;

    type_templates_hydrator h;
    std::list<type_template> r;
    for (const auto& f : files) {
        auto tts(h.hydrate(f));
        r.splice(r.end(), tts);
    }
    BOOST_LOG_SEV(lg, info) << "Finished hydrating all files.";
    return r;
}

std::list<type> type_repository_factory::instantiate_templates(
    const ownership_hierarchy_repository& ohrp,
    const std::list<type_template>& tts) const {
    std::list<type> r;

    const template_instantiator ins(ohrp);
    unsigned int counter(0);
    for (const auto tt : tts) {
        if (!ins.is_instantiable(tt.kind())) {
            r.push_back(ins.to_type(tt));
            continue;
        }

        r.splice(r.end(), ins.instantiate(tt));
        ++counter;
    }

    BOOST_LOG_SEV(lg, debug) << "Number of templates instantiated: " << counter;
    return r;
}

type_repository type_repository_factory::
create_repository(const std::list<type>& ts) const {

    type_repository r;
    r.all_types(ts);

    for (const auto& t : ts) {
        const auto n(t.name().qualified());
        const auto pair(std::make_pair(n, t));
        const auto inserted(r.types_by_name().insert(pair).second);
        if (!inserted) {
            BOOST_LOG_SEV(lg, error) << duplicate_qualified_name << n;
            BOOST_THROW_EXCEPTION(building_error(duplicate_qualified_name + n));
        }

        const auto& oh(t.ownership_hierarchy());
        if (!oh.facet_name().empty())
            r.types_by_facet_name()[oh.facet_name()].push_back(t);

        if (!oh.formatter_name().empty())
            r.types_by_formatter_name()[oh.formatter_name()]
                .push_back(t);

        if (!oh.model_name().empty())
            r.types_by_model_name()[oh.model_name()]
                .push_back(t);
    }

    return r;
}

type_repository type_repository_factory::make(
    const ownership_hierarchy_repository& ohrp,
    const std::vector<boost::filesystem::path>& dirs) const {
    BOOST_LOG_SEV(lg, info) << "Generating repository.";

    const auto original(hydrate_templates(dirs));
    const auto instantiated(instantiate_templates(ohrp, original));
    const auto r(create_repository(instantiated));

    BOOST_LOG_SEV(lg, info) << "Generated repository: " << r;
    return r;
}

} }