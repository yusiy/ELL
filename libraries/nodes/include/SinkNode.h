////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     SinkNode.h (nodes)
//  Authors:  Lisa Ong
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <model/include/CompilableNode.h>
#include <model/include/IRMapCompiler.h>
#include <model/include/ModelTransformer.h>
#include <model/include/OutputNodeBase.h>

#include <emitters/include/IRMetadata.h>

#include <functional>
#include <string>
#include <vector>

namespace ell
{
namespace nodes
{
    /// <summary> A function that the SinkNode calls to deliver data to user code. </summary>
    ///
    /// In device-side compiled code, the function signature should be:
    /// ```
    /// void SinkFunction(ValueType* data)
    /// ```
    template <typename ValueType>
    using SinkFunction = std::function<void(const std::vector<ValueType>&)>;

    template <typename ValueType>
    class SinkNode : public model::SinkNodeBase
    {
    public:
        /// @name Input and Output Ports
        /// @{
        static constexpr const char* triggerPortName = "inputTrigger";

        const model::InputPort<ValueType>& input = _input;
        const model::InputPort<bool>& trigger = _trigger;
        const model::OutputPort<ValueType>& output = _output; // maybe we don't need this because results are reported via callback
        /// @}

        SinkNode();

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="trigger"> Port elements for the trigger. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::OutputPort<ValueType>& input, const model::OutputPort<bool>& trigger, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="trigger"> Port elements for the trigger. </param>
        /// <param name="shape"> The output shape. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::OutputPort<ValueType>& input, const model::OutputPort<bool>& trigger, const model::MemoryShape& shape, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Constructor. </summary>
        ///
        /// <param name="input"> Port elements for input values. </param>
        /// <param name="trigger"> Port elements for the trigger. </param>
        /// <param name="outputVectorSize"> The output vector size. </param>
        /// <param name="sinkFunctionName"> The sink function name to be emitted. </param>
        /// <param name="sink"> The optional sink function that will receive output values. </param>
        SinkNode(const model::OutputPort<ValueType>& input, const model::OutputPort<bool>& trigger, size_t outputVectorSize, const std::string& sinkFunctionName, SinkFunction<ValueType> sink = nullptr);

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        static std::string GetTypeName() { return utilities::GetCompositeTypeName<ValueType>("SinkNode"); }

        /// <summary> Gets the name of this type (for serialization). </summary>
        ///
        /// <returns> The name of this type. </returns>
        std::string GetRuntimeTypeName() const override { return GetTypeName(); }

        /// <summary> Sets the sink function for this node for use in Compute(). </summary>
        ///
        /// <param name="function"> The sink function to set. </param>
        void SetSinkFunction(SinkFunction<ValueType> function) { _sink = function; }

    protected:
        void Compute() const override;
        void Compile(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function) override;

        utilities::ArchiveVersion GetArchiveVersion() const override;
        bool CanReadArchiveVersion(const utilities::ArchiveVersion& version) const override;
        void WriteToArchive(utilities::Archiver& archiver) const override;
        void ReadFromArchive(utilities::Unarchiver& archiver) override;
        bool HasState() const override { return true; } // stored state: callback function name, shape

    private:
        void Copy(model::ModelTransformer& transformer) const override;

        void SetOutputValuesLoop(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);
        void SetOutputValuesExpanded(model::IRMapCompiler& compiler, emitters::IRFunctionEmitter& function);

        model::InputPort<ValueType> _input;
        model::InputPort<bool> _trigger;
        model::OutputPort<ValueType> _output;

        SinkFunction<ValueType> _sink;
    };
} // namespace nodes
} // namespace ell

#include "../tcc/SinkNode.tcc"