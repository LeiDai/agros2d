// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "space_h2d_xml.h"

namespace XMLSpace
{
  // space
  // 

  const space::element_data_sequence& space::
  element_data () const
  {
    return this->element_data_;
  }

  space::element_data_sequence& space::
  element_data ()
  {
    return this->element_data_;
  }

  void space::
  element_data (const element_data_sequence& s)
  {
    this->element_data_ = s;
  }

  const space::spaceType_optional& space::
  spaceType () const
  {
    return this->spaceType_;
  }

  space::spaceType_optional& space::
  spaceType ()
  {
    return this->spaceType_;
  }

  void space::
  spaceType (const spaceType_type& x)
  {
    this->spaceType_.set (x);
  }

  void space::
  spaceType (const spaceType_optional& x)
  {
    this->spaceType_ = x;
  }

  void space::
  spaceType (::std::auto_ptr< spaceType_type > x)
  {
    this->spaceType_.set (x);
  }


  // element_data
  // 

  const element_data::e_id_type& element_data::
  e_id () const
  {
    return this->e_id_.get ();
  }

  element_data::e_id_type& element_data::
  e_id ()
  {
    return this->e_id_.get ();
  }

  void element_data::
  e_id (const e_id_type& x)
  {
    this->e_id_.set (x);
  }

  const element_data::ord_type& element_data::
  ord () const
  {
    return this->ord_.get ();
  }

  element_data::ord_type& element_data::
  ord ()
  {
    return this->ord_.get ();
  }

  void element_data::
  ord (const ord_type& x)
  {
    this->ord_.set (x);
  }

  const element_data::bd_type& element_data::
  bd () const
  {
    return this->bd_.get ();
  }

  element_data::bd_type& element_data::
  bd ()
  {
    return this->bd_.get ();
  }

  void element_data::
  bd (const bd_type& x)
  {
    this->bd_.set (x);
  }

  const element_data::n_type& element_data::
  n () const
  {
    return this->n_.get ();
  }

  element_data::n_type& element_data::
  n ()
  {
    return this->n_.get ();
  }

  void element_data::
  n (const n_type& x)
  {
    this->n_.set (x);
  }

  const element_data::chgd_type& element_data::
  chgd () const
  {
    return this->chgd_.get ();
  }

  element_data::chgd_type& element_data::
  chgd ()
  {
    return this->chgd_.get ();
  }

  void element_data::
  chgd (const chgd_type& x)
  {
    this->chgd_.set (x);
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace XMLSpace
{
  // space
  //

  space::
  space ()
  : ::xml_schema::type (),
    element_data_ (::xml_schema::flags (), this),
    spaceType_ (::xml_schema::flags (), this)
  {
  }

  space::
  space (const space& x,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    element_data_ (x.element_data_, f, this),
    spaceType_ (x.spaceType_, f, this)
  {
  }

  space::
  space (const ::xercesc::DOMElement& e,
         ::xml_schema::flags f,
         ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    element_data_ (f, this),
    spaceType_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
      this->parse (p, f);
    }
  }

  void space::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    for (; p.more_elements (); p.next_element ())
    {
      const ::xercesc::DOMElement& i (p.cur_element ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      // element_data
      //
      if (n.name () == "element_data" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< element_data_type > r (
          element_data_traits::create (i, f, this));

        this->element_data_.push_back (r);
        continue;
      }

      break;
    }

    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "spaceType" && n.namespace_ ().empty ())
      {
        ::std::auto_ptr< spaceType_type > r (
          spaceType_traits::create (i, f, this));

        this->spaceType_.set (r);
        continue;
      }
    }
  }

  space* space::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class space (*this, f, c);
  }

  space::
  ~space ()
  {
  }

  // element_data
  //

  element_data::
  element_data (const e_id_type& e_id,
                const ord_type& ord,
                const bd_type& bd,
                const n_type& n,
                const chgd_type& chgd)
  : ::xml_schema::type (),
    e_id_ (e_id, ::xml_schema::flags (), this),
    ord_ (ord, ::xml_schema::flags (), this),
    bd_ (bd, ::xml_schema::flags (), this),
    n_ (n, ::xml_schema::flags (), this),
    chgd_ (chgd, ::xml_schema::flags (), this)
  {
  }

  element_data::
  element_data (const element_data& x,
                ::xml_schema::flags f,
                ::xml_schema::container* c)
  : ::xml_schema::type (x, f, c),
    e_id_ (x.e_id_, f, this),
    ord_ (x.ord_, f, this),
    bd_ (x.bd_, f, this),
    n_ (x.n_, f, this),
    chgd_ (x.chgd_, f, this)
  {
  }

  element_data::
  element_data (const ::xercesc::DOMElement& e,
                ::xml_schema::flags f,
                ::xml_schema::container* c)
  : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
    e_id_ (f, this),
    ord_ (f, this),
    bd_ (f, this),
    n_ (f, this),
    chgd_ (f, this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
      this->parse (p, f);
    }
  }

  void element_data::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "e_id" && n.namespace_ ().empty ())
      {
        this->e_id_.set (e_id_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "ord" && n.namespace_ ().empty ())
      {
        this->ord_.set (ord_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "bd" && n.namespace_ ().empty ())
      {
        this->bd_.set (bd_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "n" && n.namespace_ ().empty ())
      {
        this->n_.set (n_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "chgd" && n.namespace_ ().empty ())
      {
        this->chgd_.set (chgd_traits::create (i, f, this));
        continue;
      }
    }

    if (!e_id_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "e_id",
        "");
    }

    if (!ord_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "ord",
        "");
    }

    if (!bd_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "bd",
        "");
    }

    if (!n_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "n",
        "");
    }

    if (!chgd_.present ())
    {
      throw ::xsd::cxx::tree::expected_attribute< char > (
        "chgd",
        "");
    }
  }

  element_data* element_data::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class element_data (*this, f, c);
  }

  element_data::
  ~element_data ()
  {
  }
}

#include <ostream>

namespace XMLSpace
{
  ::std::ostream&
  operator<< (::std::ostream& o, const space& i)
  {
    for (space::element_data_const_iterator
         b (i.element_data ().begin ()), e (i.element_data ().end ());
         b != e; ++b)
    {
      o << ::std::endl << "element_data: " << *b;
    }

    if (i.spaceType ())
    {
      o << ::std::endl << "spaceType: " << *i.spaceType ();
    }

    return o;
  }

  ::std::ostream&
  operator<< (::std::ostream& o, const element_data& i)
  {
    o << ::std::endl << "e_id: " << i.e_id ();
    o << ::std::endl << "ord: " << i.ord ();
    o << ::std::endl << "bd: " << i.bd ();
    o << ::std::endl << "n: " << i.n ();
    o << ::std::endl << "chgd: " << i.chgd ();
    return o;
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace XMLSpace
{
  ::std::auto_ptr< ::XMLSpace::space >
  space_ (const ::std::string& u,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (const ::std::string& u,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (const ::std::string& u,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        u, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::XMLSpace::space_ (isrc, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::XMLSpace::space_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is);
    return ::XMLSpace::space_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          const ::std::string& sid,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::XMLSpace::space_ (isrc, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          const ::std::string& sid,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0,
      (f & ::xml_schema::flags::keep_dom) == 0);

    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::XMLSpace::space_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::std::istream& is,
          const ::std::string& sid,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
    return ::XMLSpace::space_ (isrc, h, f, p);
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::xercesc::InputSource& i,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xsd::cxx::tree::error_handler< char > h;

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::xercesc::InputSource& i,
          ::xml_schema::error_handler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::xercesc::InputSource& i,
          ::xercesc::DOMErrorHandler& h,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::parse< char > (
        i, h, p, f));

    if (!d.get ())
      throw ::xsd::cxx::tree::parsing< char > ();

    ::std::auto_ptr< ::XMLSpace::space > r (
      ::XMLSpace::space_ (
        d, f | ::xml_schema::flags::own_dom, p));

    return r;
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (const ::xercesc::DOMDocument& d,
          ::xml_schema::flags f,
          const ::xml_schema::properties& p)
  {
    if (f & ::xml_schema::flags::keep_dom)
    {
      ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
        static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

      ::std::auto_ptr< ::XMLSpace::space > r (
        ::XMLSpace::space_ (
          c, f | ::xml_schema::flags::own_dom, p));

      return r;
    }

    const ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "space" &&
        n.namespace_ () == "XMLSpace")
    {
      ::std::auto_ptr< ::XMLSpace::space > r (
        ::xsd::cxx::tree::traits< ::XMLSpace::space, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "space",
      "XMLSpace");
  }

  ::std::auto_ptr< ::XMLSpace::space >
  space_ (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
          ::xml_schema::flags f,
          const ::xml_schema::properties&)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
      ((f & ::xml_schema::flags::keep_dom) &&
       !(f & ::xml_schema::flags::own_dom))
      ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
      : 0);

    ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
    const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (f & ::xml_schema::flags::keep_dom)
      doc.setUserData (::xml_schema::dom::tree_node_key,
                       (c.get () ? &c : &d),
                       0);

    if (n.name () == "space" &&
        n.namespace_ () == "XMLSpace")
    {
      ::std::auto_ptr< ::XMLSpace::space > r (
        ::xsd::cxx::tree::traits< ::XMLSpace::space, char >::create (
          e, f, 0));
      return r;
    }

    throw ::xsd::cxx::tree::unexpected_element < char > (
      n.name (),
      n.namespace_ (),
      "space",
      "XMLSpace");
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace XMLSpace
{
  void
  space_ (::std::ostream& o,
          const ::XMLSpace::space& s,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  space_ (::std::ostream& o,
          const ::XMLSpace::space& s,
          ::xml_schema::error_handler& h,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xsd::cxx::xml::auto_initializer i (
      (f & ::xml_schema::flags::dont_initialize) == 0);

    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  space_ (::std::ostream& o,
          const ::XMLSpace::space& s,
          ::xercesc::DOMErrorHandler& h,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));
    ::xsd::cxx::xml::dom::ostream_format_target t (o);
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  space_ (::xercesc::XMLFormatTarget& t,
          const ::XMLSpace::space& s,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));

    ::xsd::cxx::tree::error_handler< char > h;

    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
    }
  }

  void
  space_ (::xercesc::XMLFormatTarget& t,
          const ::XMLSpace::space& s,
          ::xml_schema::error_handler& h,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  space_ (::xercesc::XMLFormatTarget& t,
          const ::XMLSpace::space& s,
          ::xercesc::DOMErrorHandler& h,
          const ::xml_schema::namespace_infomap& m,
          const ::std::string& e,
          ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::XMLSpace::space_ (s, m, f));
    if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
    {
      throw ::xsd::cxx::tree::serialization< char > ();
    }
  }

  void
  space_ (::xercesc::DOMDocument& d,
          const ::XMLSpace::space& s,
          ::xml_schema::flags)
  {
    ::xercesc::DOMElement& e (*d.getDocumentElement ());
    const ::xsd::cxx::xml::qualified_name< char > n (
      ::xsd::cxx::xml::dom::name< char > (e));

    if (n.name () == "space" &&
        n.namespace_ () == "XMLSpace")
    {
      e << s;
    }
    else
    {
      throw ::xsd::cxx::tree::unexpected_element < char > (
        n.name (),
        n.namespace_ (),
        "space",
        "XMLSpace");
    }
  }

  ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
  space_ (const ::XMLSpace::space& s,
          const ::xml_schema::namespace_infomap& m,
          ::xml_schema::flags f)
  {
    ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
      ::xsd::cxx::xml::dom::serialize< char > (
        "space",
        "XMLSpace",
        m, f));

    ::XMLSpace::space_ (*d, s, f);
    return d;
  }

  void
  operator<< (::xercesc::DOMElement& e, const space& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // element_data
    //
    for (space::element_data_const_iterator
         b (i.element_data ().begin ()), n (i.element_data ().end ());
         b != n; ++b)
    {
      ::xercesc::DOMElement& s (
        ::xsd::cxx::xml::dom::create_element (
          "element_data",
          e));

      s << *b;
    }

    // spaceType
    //
    if (i.spaceType ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "spaceType",
          e));

      a << *i.spaceType ();
    }
  }

  void
  operator<< (::xercesc::DOMElement& e, const element_data& i)
  {
    e << static_cast< const ::xml_schema::type& > (i);

    // e_id
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "e_id",
          e));

      a << i.e_id ();
    }

    // ord
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "ord",
          e));

      a << i.ord ();
    }

    // bd
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "bd",
          e));

      a << i.bd ();
    }

    // n
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "n",
          e));

      a << i.n ();
    }

    // chgd
    //
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "chgd",
          e));

      a << i.chgd ();
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

