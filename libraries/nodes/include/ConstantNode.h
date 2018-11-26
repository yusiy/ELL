////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     ConstantNode.h (nodes)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <model/include/CompilableNode.h>
#include <model/include/CompilableNodeUtilities.h>
#include <model/include/IRMapCompiler.h>
#include <model/include/MapCompiler.h>
#include <model/include/ModelTransformer.h>
#include <model/include/OutputPort.h>

#include <emitters/include/IRFunctionEmitter.h>

#include <predictors/include/ConstantPredictor.h>

#include <utilities/include/IArchivable.h>
#include <utilities/include/TypeName.h>

#include <memory>
#include <vector>

namespace ell
{
/// <summary> nodes namespace </summary>
namespace nodes
{
    /// <summary> A node that contains a constant value. Has no inputs. </summary>
    template <typename ValueType>
    class ConstantNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        ConstantNode();

        /// <summary> Constructor for a scalar constant </summary>
        ///
        /// <param name="value"> The scalar value </param>
        ConstantNode(ValueType value);

        /// Constructor for a vector constant
        ///
        /// <param name="value"> The vector value </param>
        ConstantNode(const std::vector<ValueType>& values);

        /// Constructor for an arbitrary-shaped array constant
        ///
        /// <param name="value"> The vector value </param>
        /// <param name="shape"> The shape of the output data </param>
        ConstantNode(const std::vector<ValueType>& values, const model::MemoryShape& shape);

        /// Constructor for an arbitrary-shaped array constant
        ///
        /// <param name="value"> The vector value </param>
        /// <param name="layout"> The memory layout of the output data </param>
        ConstantNode(const std::vector<ValueType>& values, const model::PortMemoryLayout& layout);

        /// <summary> Gets the values contained in this node </summary>
        ///
        /// <returns> The values contained in this node </returns>
        const std::vector<ValueType>& GetValues() const { return _values; }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("ConstantNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

    protected:
        void Compute() const override;
        void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;
        bool HasState() const override { return true; }
        bool ShouldCompileInline() const override { return true; }
        utilities::ArchiveVersion GetArchiveVersion() const override;
        bool CanReadArchiveVersion(const utilities::ArchiveVersion& version) const override;
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;

    private:
        void Copy(model::ModelTransformer& transformer) const override;

        // Output
        model::OutputPort<ValueType> _output;

        // Constant value
        std::vector<ValueType> _values;
    };

    /// <summary> Adds a constant node (which represents a constant predictor) to a model transformer. </summary>
    ///
    /// <param name="input"> The input to the predictor, which is ignored. </param>
    /// <param name="predictor"> The constant predictor. </param>
    /// <param name="transformer"> [in,out] The model transformer. </param>
    ///
    /// <returns> The node added to the model. </returns>
    ConstantNode<double>* AddNodeToModelTransformer(const model::PortElements<double>& input, const predictors::ConstantPredictor& predictor, model::ModelTransformer& transformer);
} // namespace nodes
} // namespace ell

#include "../tcc/ConstantNode.tcc"
