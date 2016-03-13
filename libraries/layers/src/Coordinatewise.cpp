////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  [projectName]
//  File:     Coordinatewise.cpp (layers)
//  Authors:  Ofer Dekel
//
//  [copyright]
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Coordinatewise.h"

// stl
#include <stdexcept>
#include <string>

namespace layers
{
    Coordinatewise::Coordinatewise(Type type) : Layer(type)
    {
        if (type == Type::scale)
        {
            _operation = std::multiplies<double>();
        }
        else if (type == Type::shift)
        {
            _operation = std::plus<double>();
        }
        else
        {
            throw std::runtime_error("this place in the code should never be reached");
        }
    }

    Coordinatewise::Coordinatewise(double value, Coordinate coordinate, Type type) : Coordinatewise(type)
    {
        _values.push_back(value);
        _inputCoordinates.push_back(coordinate);
    }

    Coordinatewise::Coordinatewise(const std::vector<double>& values, const CoordinateList& coordinates, Type type) : Coordinatewise(type)
    {
        _values = values;
        _inputCoordinates = coordinates;
    }

    uint64 Coordinatewise::Size() const
    {
        return _inputCoordinates.size();
    }

    void Coordinatewise::Compute(const std::vector<std::vector<double>>& inputs, std::vector<double>& outputs) const
    {
        for(uint64 k=0; k<_values.size(); ++k)
        {
            Coordinate coordinate = _inputCoordinates[k];
            double input = inputs[coordinate.GetLayerIndex()][coordinate.GetElementIndex()];
            outputs[k] = _operation(_values[k], input);
        }
    }

    Layer::InputCoordinateIterator Coordinatewise::GetInputCoordinates(uint64 index) const
    {
        return Layer::InputCoordinateIterator(_inputCoordinates.cbegin()+index, _inputCoordinates.cbegin()+index+1);
    }

    const char* Coordinatewise::GetTypeName()
    {
        return "Coordinatewise";
    }

    const char* Coordinatewise::GetRuntimeTypeName() const
    {
        return GetTypeName();
    }

    void Coordinatewise::Read(utilities::XMLDeserializer& deserializer)
    {
        //int version = 0;
        //deserializer.Deserialize("version", version);
        //if (version == 1)
        //{
        //    deserializer.Deserialize("values", _values);
        //    deserializer.Deserialize("coordinates", _inputCoordinates);
        //}
        //else
        //{
        //    throw std::runtime_error("unsupported version: " + std::to_string(version));
        //}
    }

    void Coordinatewise::Write(utilities::XMLSerializer& serializer) const
    {
        //serializer.Serialize("version", _currentVersion);
        //serializer.Serialize("values", _values);
        //serializer.Serialize("coordinates", _inputCoordinates);
    }

    void Coordinatewise::Serialize(utilities::JsonSerializer& serializer) const
    {
        // version 1
        Layer::SerializeHeader(serializer, 1);
        serializer.Write("values", _values);
        serializer.Write("coordinates", _inputCoordinates);
    }

    void Coordinatewise::Deserialize(utilities::JsonSerializer& serializer, int version)
    {
        if(version == 1)
        {
            serializer.Read("values", _values);
            serializer.Read("coordinates", _inputCoordinates);
        }
        else
        {
            throw std::runtime_error("unsupported version: " + std::to_string(version));
        }
    }
}


