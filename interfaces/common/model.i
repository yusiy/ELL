////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     model.i (interfaces)
//  Authors:  Chuck Jacobs, Kirk Olynyk
//
////////////////////////////////////////////////////////////////////////////////////////////////////

%{
#include "ModelInterface.h"
#include "ModelBuilderInterface.h"

#include <utilities/include/Variant.h>
#include <vector>
%}

// Language-specific callable wrappers for Map callbacks
WRAP_CALLABLE_AS_MAP_INPUT_CALLBACK(DoubleCallbackBase, double)
WRAP_CALLABLE_AS_MAP_INPUT_CALLBACK(FloatCallbackBase, float)
WRAP_CALLABLE_AS_MAP_OUTPUT_CALLBACK(DoubleCallbackBase, double)
WRAP_CALLABLE_AS_MAP_OUTPUT_CALLBACK(FloatCallbackBase, float)

// Language-specific callable wrappers for CompiledMap callbacks
WRAP_CALLABLES_AS_COMPILED_MAP_CALLBACKS(DoubleCallbackBase, DoubleCallbackBase, double)
WRAP_CALLABLES_AS_COMPILED_MAP_CALLBACKS(FloatCallbackBase, FloatCallbackBase, float)

// naturalvar declarations for members that are object types (see ..\Readme.md)
%naturalvar ELL_API::PortMemoryLayout::size;
%naturalvar ELL_API::PortMemoryLayout::padding;
%naturalvar ELL_API::PortMemoryLayout::offset;
%naturalvar ELL_API::PortMemoryLayout::order;

// Include the C++ code to be wrapped
%include "ModelInterface.h"
%include "ModelBuilderInterface.h"
%include "macros.i"

// Template instantiations
%template(RegisterCallbacksDouble) ELL_API::CompiledMap::RegisterCallbacks<double>;
%template(RegisterCallbacksFloat) ELL_API::CompiledMap::RegisterCallbacks<float>;
%template(UnregisterCallbacksDouble) ELL_API::CompiledMap::UnregisterCallbacks<double>;
%template(UnregisterCallbacksFloat) ELL_API::CompiledMap::UnregisterCallbacks<float>;
%template(StepDouble) ELL_API::CompiledMap::Step<double>;
%template(StepFloat) ELL_API::CompiledMap::Step<float>;

%template(SetSinkCallbackDouble) ELL_API::Map::SetSinkCallback<double>;
%template(SetSinkCallbackFloat) ELL_API::Map::SetSinkCallback<float>;
%template(SetSourceCallbackDouble) ELL_API::Map::SetSourceCallback<double>;
%template(SetSourceCallbackFloat) ELL_API::Map::SetSourceCallback<float>;
%template(StepDouble) ELL_API::Map::Step<double>;
%template(StepFloat) ELL_API::Map::Step<float>;

#ifndef SWIGXML
%include "std_vector.i"

%template(PortElementsList) std::vector<ELL_API::PortElements*>;

#endif

#ifdef SWIGPYTHON
    %include "model_python_post.i"
#elif SWIGJAVASCRIPT
    %include "model_javascript_post.i"
#endif
