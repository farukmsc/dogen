// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_REGION_ODB_PGSQL_HXX
#define DOGEN_NORTHWIND_ODB_REGION_ODB_PGSQL_HXX

// Begin prologue.
//
#include <odb/boost/version.hxx>
#if ODB_BOOST_VERSION != 2040000 // 2.4.0
#  error ODB and C++ compilers see different libodb-boost interface versions
#endif
#include <boost/shared_ptr.hpp>
#include <odb/boost/smart-ptr/pointer-traits.hxx>
#include <odb/boost/smart-ptr/wrapper-traits.hxx>
#include <odb/boost/optional/wrapper-traits.hxx>
#include <odb/boost/unordered/container-traits.hxx>
#include <odb/boost/date-time/pgsql/gregorian-traits.hxx>
#include <odb/boost/date-time/pgsql/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/pgsql/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/northwind/types/region.hpp"

#include "dogen/test_models/northwind/types/region_id-odb-pgsql.hxx"

#include "dogen/northwind/odb/region-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/pgsql/version.hxx>
#include <odb/pgsql/forward.hxx>
#include <odb/pgsql/binding.hxx>
#include <odb/pgsql/pgsql-types.hxx>
#include <odb/pgsql/query.hxx>

namespace odb
{
  // region
  //
  template <typename A>
  struct query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >
  {
    // region_id
    //
    struct region_id_class_
    {
      region_id_class_ ()
      {
      }

      // value
      //
      typedef
      pgsql::query_column<
        pgsql::value_traits<
          int,
          pgsql::id_integer >::query_type,
        pgsql::id_integer >
      value_type_;

      static const value_type_ value;
    };

    static const region_id_class_ region_id;

    // region_description
    //
    typedef
    pgsql::query_column<
      pgsql::value_traits<
        ::std::string,
        pgsql::id_string >::query_type,
      pgsql::id_string >
    region_description_type_;

    static const region_description_type_ region_description;
  };

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::region_id_class_::value_type_
  query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::region_id_class_::
  value (A::table_name, "\"REGION_ID\"", 0);

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::region_id_class_
  query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::region_id;

  template <typename A>
  const typename query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::region_description_type_
  query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >::
  region_description (A::table_name, "\"REGION_DESCRIPTION\"", 0);

  template <typename A>
  struct pointer_query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >:
    query_columns< ::dogen::test_models::northwind::region, id_pgsql, A >
  {
  };

  template <>
  class access::object_traits_impl< ::dogen::test_models::northwind::region, id_pgsql >:
    public access::object_traits< ::dogen::test_models::northwind::region >
  {
    public:
    struct id_image_type
    {
      composite_value_traits< ::dogen::test_models::northwind::region_id, id_pgsql >::image_type id_value;

      std::size_t version;
    };

    struct image_type
    {
      // region_id_
      //
      composite_value_traits< ::dogen::test_models::northwind::region_id, id_pgsql >::image_type region_id_value;

      // region_description_
      //
      details::buffer region_description_value;
      std::size_t region_description_size;
      bool region_description_null;

      std::size_t version;
    };

    struct extra_statement_cache_type;

    using object_traits<object_type>::id;

    static id_type
    id (const image_type&);

    static bool
    grow (image_type&,
          bool*);

    static void
    bind (pgsql::bind*,
          image_type&,
          pgsql::statement_kind);

    static void
    bind (pgsql::bind*, id_image_type&);

    static bool
    init (image_type&,
          const object_type&,
          pgsql::statement_kind);

    static void
    init (object_type&,
          const image_type&,
          database*);

    static void
    init (id_image_type&, const id_type&);

    typedef pgsql::object_statements<object_type> statements_type;

    typedef pgsql::query_base query_base_type;

    static const std::size_t column_count = 2UL;
    static const std::size_t id_column_count = 1UL;
    static const std::size_t inverse_column_count = 0UL;
    static const std::size_t readonly_column_count = 0UL;
    static const std::size_t managed_optimistic_column_count = 0UL;

    static const std::size_t separate_load_column_count = 0UL;
    static const std::size_t separate_update_column_count = 0UL;

    static const bool versioned = false;

    static const char persist_statement[];
    static const char find_statement[];
    static const char update_statement[];
    static const char erase_statement[];
    static const char query_statement[];
    static const char erase_query_statement[];

    static const char table_name[];

    static void
    persist (database&, const object_type&);

    static pointer_type
    find (database&, const id_type&);

    static bool
    find (database&, const id_type&, object_type&);

    static bool
    reload (database&, object_type&);

    static void
    update (database&, const object_type&);

    static void
    erase (database&, const id_type&);

    static void
    erase (database&, const object_type&);

    static result<object_type>
    query (database&, const query_base_type&);

    static unsigned long long
    erase_query (database&, const query_base_type&);

    static const char persist_statement_name[];
    static const char find_statement_name[];
    static const char update_statement_name[];
    static const char erase_statement_name[];
    static const char query_statement_name[];
    static const char erase_query_statement_name[];

    static const unsigned int persist_statement_types[];
    static const unsigned int find_statement_types[];
    static const unsigned int update_statement_types[];

    public:
    static bool
    find_ (statements_type&,
           const id_type*);

    static void
    load_ (statements_type&,
           object_type&,
           bool reload);
  };

  // region
  //
}

#include "dogen/northwind/odb/region-odb-pgsql.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_REGION_ODB_PGSQL_HXX