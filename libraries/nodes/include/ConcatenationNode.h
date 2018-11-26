////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     ConcatenationNode.h (nodes)
//  Authors:  Byron Changuion
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <model/include/CompilableNode.h>
#include <model/include/CompilableNodeUtilities.h>
#include <model/include/IRMapCompiler.h>
#include <model/include/Model.h>
#include <model/include/ModelTransformer.h>
#include <model/include/Node.h>

#include <utilities/include/Exception.h>
#include <utilities/include/IArchivable.h>
#include <utilities/include/TypeName.h>

#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A node that concatenates inputs from a number of nodes. </summary>
    template <typename ValueType>
    class ConcatenationNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* shapeName = "shape";
        const model::InputPort<ValueType>& input = _input;
        const model::OutputPort<ValueType>& output = _output;

        /// @}

        /// <summary> Default Constructor </summary>
        ConcatenationNode();

        /// <summary> Constructor </summary>
        /// <param name="input"> The inputs to concatenate specified as a PortElements. </param>
        ConcatenationNode(const model::OutputPort<ValueType>& input);

        /// <summary> Constructor </summary>
        /// <param name="input"> The inputs to concatenate specified as a PortElements. </param>
        /// <param name="shape"> The shape of the output data. </param>
        ConcatenationNode(const model::OutputPort<ValueType>& input, const model::MemoryShape& shape);

        /// <summary> Gets the output shape. </summary>
        ///
        /// <returns> The output shape. </returns>
        model::MemoryShape GetShape() const { return _output.GetMemoryLayout().GetActiveSize(); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("ConcatenationNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

    protected:
        void Compute() const override;
        void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;
        bool ShouldCompileInline() const override { return true; }
        bool HasState() const override { return true; }
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;

        void SetShape(const model::MemoryShape& shape) { _output.SetMemoryLayout({ shape }); }

    private:
        void Copy(model::ModelTransformer& transformer) const override;

        model::InputPort<ValueType> _input;
        model::OutputPort<ValueType> _output;
    };
} // namespace nodes
} // namespace ell

#include "../tcc/ConcatenationNode.tcc"