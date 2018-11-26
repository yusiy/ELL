////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     IRMapCompiler.tcc (model)
//  Authors:  Umesh Madan, Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ell
{
namespace model
{
    template <typename ValueType>
    emitters::LLVMValue IRMapCompiler::EnsurePortEmitted(const OutputPortBase& port, ValueType initialValue)
    {
        using namespace logging;

        Log() << "EnsurePortEmitted called for port " << port.GetRuntimeTypeName() << EOL;
        auto pVar = GetOrAllocatePortVariable(port, initialValue);
        return GetModule().EnsureEmitted(*pVar);
    }
} // namespace model
} // namespace ell
