////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     HammingWindowNode.h (nodes)
//  Authors:  Chuck Jacobs
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "BinaryOperationNode.h"
#include "ConstantNode.h"

#include <dsp/include/WindowFunctions.h>

#include <model/include/Model.h>
#include <model/include/ModelTransformer.h>
#include <model/include/Node.h>

#include <string>

namespace ell
{
namespace nodes
{
    /// <summary> A node that contains data for a Hamming window. </summary>
    ///
    /// <typeparam name="ValueType"> The element type. </typeparam>
    ///
    template <typename ValueType>
    class HammingWindowNode : public model::Node
    {
    public:
        /// @name Input and Output Ports
        /// @{
        const model::InputPort<ValueType>& input = _input;
        const model::OutputPort<ValueType>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        HammingWindowNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="input"> The signal to apply the window to. </param>
        HammingWindowNode(const model::OutputPort<ValueType>& input);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("HammingWindowNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

    protected:
        void Compute() const override;
        bool Refine(model::ModelTransformer& transformer) const override;
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;
        bool HasState() const override { return true; }

    private:
        void Copy(model::ModelTransformer& transformer) const override;

        // Input
        model::InputPort<ValueType> _input;

        // Output
        model::OutputPort<ValueType> _output;
    };
} // namespace nodes
} // namespace ell

#include "../tcc/HammingWindowNode.tcc"
