// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

namespace odb
{
  // products
  //

  inline
  access::object_traits< ::dogen::test_models::northwind::products >::id_type
  access::object_traits< ::dogen::test_models::northwind::products >::
  id (const object_type& o)
  {
    return o.product_id ();
  }

  inline
  void access::object_traits< ::dogen::test_models::northwind::products >::
  callback (database& db, object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }

  inline
  void access::object_traits< ::dogen::test_models::northwind::products >::
  callback (database& db, const object_type& x, callback_event e)
  {
    ODB_POTENTIALLY_UNUSED (db);
    ODB_POTENTIALLY_UNUSED (x);
    ODB_POTENTIALLY_UNUSED (e);
  }
}

