// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#ifndef DOGEN_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX
#define DOGEN_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX

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
#include <odb/boost/date-time/oracle/gregorian-traits.hxx>
#include <odb/boost/date-time/oracle/posix-time-traits.hxx>
#include <odb/boost/multi-index/container-traits.hxx>
#include <odb/boost/uuid/oracle/uuid-traits.hxx>
//
// End prologue.

#include <odb/version.hxx>

#if (ODB_VERSION != 20400UL)
#error ODB runtime version mismatch
#endif

#include <odb/pre.hxx>

#include "dogen/northwind/types/repository.hpp"

#include "dogen/test_models/northwind/types/categories-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/category_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customer_customer_demo-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customer_customer_demo_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customer_demographics-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customer_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customer_type_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/customers-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/employee_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/employee_territories-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/employee_territories_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/employees-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/order_details-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/order_details_key-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/order_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/product_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/products-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/region-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/region_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/shipper_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/shippers-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/supplier-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/supplier_id-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/territory-odb-oracle.hxx"
#include "dogen/test_models/northwind/types/territory_id-odb-oracle.hxx"

#include "dogen/northwind/odb/repository-odb.hxx"

#include <odb/details/buffer.hxx>

#include <odb/oracle/version.hxx>
#include <odb/oracle/forward.hxx>
#include <odb/oracle/binding.hxx>
#include <odb/oracle/oracle-types.hxx>
#include <odb/oracle/query.hxx>

namespace odb
{
}

#include "dogen/northwind/odb/repository-odb-oracle.ixx"

#include <odb/post.hxx>

#endif // DOGEN_NORTHWIND_ODB_REPOSITORY_ODB_ORACLE_HXX