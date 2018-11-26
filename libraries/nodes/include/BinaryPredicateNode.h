////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     BinaryPredicateNode.h (nodes)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <model/include/CompilableNode.h>
#include <model/include/CompilableNodeUtilities.h>
#include <model/include/IRMapCompiler.h>
#include <model/include/Model.h>
#include <model/include/ModelTransformer.h>
#include <model/include/Node.h>

#include <emitters/include/EmitterTypes.h>

#include <utilities/include/Exception.h>
#include <utilities/include/IArchivable.h>
#include <utilities/include/TypeName.h>

#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A node that performs a coordinatewise binary boolean-valued operation on its inputs. </summary>
    template <typename ValueType>
    class BinaryPredicateNode : public model::CompilableNode
    {
    public:
        /// @name Input and Output Ports
        /// @{
        const model::InputPort<ValueType>& input1 = _input1;
        const model::InputPort<ValueType>& input2 = _input2;
        const model::OutputPort<bool>& output = _output;
        /// @}

        /// <summary> Default Constructor </summary>
        BinaryPredicateNode();

        /// <summary> Constructor </summary>
        ///
        /// <param name="input1"> The left-hand input of the arithmetic expression. </param>
        /// <param name="input2"> The right-hand input of the arithmetic expression. </param>
        /// <param name="predicate"> The type of predicate to apply. </param>
        BinaryPredicateNode(const model::OutputPort<ValueType>& input1, const model::OutputPort<ValueType>& input2, emitters::BinaryPredicateType predicate);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("BinaryPredicateNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Gets the predicate performed by this node </summary>
        ///
        /// <returns> The predicate </returns>
        emitters::BinaryPredicateType GetPredicate() const { return _predicate; }

    protected:
        void Compute() const override;

        template <typename Operation>
        std::vector<bool> ComputeOutput(Operation&& fn) const;

        void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;
        bool HasState() const override { return true; } // stored state: predicate

    private:
        void Copy(model::ModelTransformer& transformer) const override;

        void CompileLoop(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void CompileExpanded(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);

        // Inputs
        model::InputPort<ValueType> _input1;
        model::InputPort<ValueType> _input2;

        // Output
        model::OutputPort<bool> _output;

        // Operation
        emitters::BinaryPredicateType _predicate;
    };
} // namespace nodes
} // namespace ell

#include "../tcc/BinaryPredicateNode.tcc"