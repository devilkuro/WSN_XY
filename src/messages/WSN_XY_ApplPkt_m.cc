//
// Generated file, do not edit! Created by opp_msgc 4.4 from messages/WSN_XY_ApplPkt.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "WSN_XY_ApplPkt_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




Register_Class(WSN_XY_ApplPkt);

WSN_XY_ApplPkt::WSN_XY_ApplPkt(const char *name, int kind) : ::ApplPkt(name,kind)
{
    this->i_var = 0;
    this->j_var = 0;
    this->u_var = 0;
    this->v_var = 0;
}

WSN_XY_ApplPkt::WSN_XY_ApplPkt(const WSN_XY_ApplPkt& other) : ::ApplPkt(other)
{
    copy(other);
}

WSN_XY_ApplPkt::~WSN_XY_ApplPkt()
{
}

WSN_XY_ApplPkt& WSN_XY_ApplPkt::operator=(const WSN_XY_ApplPkt& other)
{
    if (this==&other) return *this;
    ::ApplPkt::operator=(other);
    copy(other);
    return *this;
}

void WSN_XY_ApplPkt::copy(const WSN_XY_ApplPkt& other)
{
    this->i_var = other.i_var;
    this->j_var = other.j_var;
    this->u_var = other.u_var;
    this->v_var = other.v_var;
}

void WSN_XY_ApplPkt::parsimPack(cCommBuffer *b)
{
    ::ApplPkt::parsimPack(b);
    doPacking(b,this->i_var);
    doPacking(b,this->j_var);
    doPacking(b,this->u_var);
    doPacking(b,this->v_var);
}

void WSN_XY_ApplPkt::parsimUnpack(cCommBuffer *b)
{
    ::ApplPkt::parsimUnpack(b);
    doUnpacking(b,this->i_var);
    doUnpacking(b,this->j_var);
    doUnpacking(b,this->u_var);
    doUnpacking(b,this->v_var);
}

int WSN_XY_ApplPkt::getI() const
{
    return i_var;
}

void WSN_XY_ApplPkt::setI(int i)
{
    this->i_var = i;
}

int WSN_XY_ApplPkt::getJ() const
{
    return j_var;
}

void WSN_XY_ApplPkt::setJ(int j)
{
    this->j_var = j;
}

int WSN_XY_ApplPkt::getU() const
{
    return u_var;
}

void WSN_XY_ApplPkt::setU(int u)
{
    this->u_var = u;
}

int WSN_XY_ApplPkt::getV() const
{
    return v_var;
}

void WSN_XY_ApplPkt::setV(int v)
{
    this->v_var = v;
}

class WSN_XY_ApplPktDescriptor : public cClassDescriptor
{
  public:
    WSN_XY_ApplPktDescriptor();
    virtual ~WSN_XY_ApplPktDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(WSN_XY_ApplPktDescriptor);

WSN_XY_ApplPktDescriptor::WSN_XY_ApplPktDescriptor() : cClassDescriptor("WSN_XY_ApplPkt", "ApplPkt")
{
}

WSN_XY_ApplPktDescriptor::~WSN_XY_ApplPktDescriptor()
{
}

bool WSN_XY_ApplPktDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<WSN_XY_ApplPkt *>(obj)!=NULL;
}

const char *WSN_XY_ApplPktDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int WSN_XY_ApplPktDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int WSN_XY_ApplPktDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *WSN_XY_ApplPktDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "i",
        "j",
        "u",
        "v",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int WSN_XY_ApplPktDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "i")==0) return base+0;
    if (fieldName[0]=='j' && strcmp(fieldName, "j")==0) return base+1;
    if (fieldName[0]=='u' && strcmp(fieldName, "u")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "v")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *WSN_XY_ApplPktDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *WSN_XY_ApplPktDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int WSN_XY_ApplPktDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    WSN_XY_ApplPkt *pp = (WSN_XY_ApplPkt *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string WSN_XY_ApplPktDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    WSN_XY_ApplPkt *pp = (WSN_XY_ApplPkt *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getI());
        case 1: return long2string(pp->getJ());
        case 2: return long2string(pp->getU());
        case 3: return long2string(pp->getV());
        default: return "";
    }
}

bool WSN_XY_ApplPktDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    WSN_XY_ApplPkt *pp = (WSN_XY_ApplPkt *)object; (void)pp;
    switch (field) {
        case 0: pp->setI(string2long(value)); return true;
        case 1: pp->setJ(string2long(value)); return true;
        case 2: pp->setU(string2long(value)); return true;
        case 3: pp->setV(string2long(value)); return true;
        default: return false;
    }
}

const char *WSN_XY_ApplPktDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *WSN_XY_ApplPktDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    WSN_XY_ApplPkt *pp = (WSN_XY_ApplPkt *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


