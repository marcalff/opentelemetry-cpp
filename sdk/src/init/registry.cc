// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "opentelemetry/baggage/propagation/baggage_propagator.h"
#include "opentelemetry/context/propagation/text_map_propagator.h"
#include "opentelemetry/sdk/init/registry.h"
#include "opentelemetry/sdk/init/text_map_propagator_builder.h"
#include "opentelemetry/trace/propagation/b3_propagator.h"
#include "opentelemetry/trace/propagation/http_trace_context.h"
#include "opentelemetry/version.h"

#ifndef OPENTELEMETRY_NO_DEPRECATED_CODE
#  include "opentelemetry/trace/propagation/jaeger.h"
#endif /* OPENTELEMETRY_NO_DEPRECATED_CODE */

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace init
{

class TraceContextBuilder : public TextMapPropagatorBuilder
{
public:
  TraceContextBuilder()                   = default;
  virtual ~TraceContextBuilder() override = default;

  std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator> Build() const override
  {
    return std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        new opentelemetry::trace::propagation::HttpTraceContext());
  }
};

class BaggageBuilder : public TextMapPropagatorBuilder
{
public:
  BaggageBuilder()                   = default;
  virtual ~BaggageBuilder() override = default;

  std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator> Build() const override
  {
    return std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        new opentelemetry::baggage::propagation::BaggagePropagator());
  }
};

class B3Builder : public TextMapPropagatorBuilder
{
public:
  B3Builder()                   = default;
  virtual ~B3Builder() override = default;

  std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator> Build() const override
  {
    return std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        new opentelemetry::trace::propagation::B3Propagator());
  }
};

class B3MultiBuilder : public TextMapPropagatorBuilder
{
public:
  B3MultiBuilder()                   = default;
  virtual ~B3MultiBuilder() override = default;

  std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator> Build() const override
  {
    return std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        new opentelemetry::trace::propagation::B3PropagatorMultiHeader());
  }
};

#ifndef OPENTELEMETRY_NO_DEPRECATED_CODE
class JaegerBuilder : public TextMapPropagatorBuilder
{
public:
  JaegerBuilder()                   = default;
  virtual ~JaegerBuilder() override = default;

  std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator> Build() const override
  {
    return std::unique_ptr<opentelemetry::context::propagation::TextMapPropagator>(
        new opentelemetry::trace::propagation::JaegerPropagator());
  }
};
#endif /* OPENTELEMETRY_NO_DEPRECATED_CODE */

static TraceContextBuilder trace_context_builder;
static BaggageBuilder baggage_builder;
static B3Builder b3_builder;
static B3MultiBuilder b3_multi_builder;

#ifndef OPENTELEMETRY_NO_DEPRECATED_CODE
static JaegerBuilder jaeger_builder;
#endif /* OPENTELEMETRY_NO_DEPRECATED_CODE */

Registry::Registry()
{
  std::pair<std::string, TextMapPropagatorBuilder *> entry;

  entry = {"tracecontext", &trace_context_builder};
  m_propagator_builders.insert(entry);

  entry = {"baggage", &baggage_builder};
  m_propagator_builders.insert(entry);

  entry = {"b3", &b3_builder};
  m_propagator_builders.insert(entry);

  entry = {"b3multi", &b3_multi_builder};
  m_propagator_builders.insert(entry);

#ifndef OPENTELEMETRY_NO_DEPRECATED_CODE
  entry = {"jaeger", &jaeger_builder};
  m_propagator_builders.insert(entry);
#endif /* OPENTELEMETRY_NO_DEPRECATED_CODE */
}

const TextMapPropagatorBuilder *Registry::GetTextMapPropagatorBuilder(const std::string &name)
{
  TextMapPropagatorBuilder *builder = nullptr;
  auto search                       = m_propagator_builders.find(name);
  if (search != m_propagator_builders.end())
  {
    builder = search->second;
  }
  return builder;
}

void Registry::AddTextMapPropagatorBuilder(const std::string &name,
                                           TextMapPropagatorBuilder *builder)
{
  std::pair<std::string, TextMapPropagatorBuilder *> entry{name, builder};
  m_propagator_builders.insert(entry);
}

const ExtensionSamplerBuilder *Registry::GetExtensionSamplerBuilder(const std::string &name)
{
  ExtensionSamplerBuilder *builder = nullptr;
  auto search                      = m_sampler_builders.find(name);
  if (search != m_sampler_builders.end())
  {
    builder = search->second;
  }
  return builder;
}

void Registry::AddExtensionSamplerBuilder(const std::string &name, ExtensionSamplerBuilder *builder)
{
  std::pair<std::string, ExtensionSamplerBuilder *> entry{name, builder};
  m_sampler_builders.insert(entry);
}

const ExtensionSpanExporterBuilder *Registry::GetExtensionSpanExporterBuilder(
    const std::string &name)
{
  ExtensionSpanExporterBuilder *builder = nullptr;
  auto search                           = m_span_exporter_builders.find(name);
  if (search != m_span_exporter_builders.end())
  {
    builder = search->second;
  }
  return builder;
}

void Registry::AddExtensionSpanExporterBuilder(const std::string &name,
                                               ExtensionSpanExporterBuilder *builder)
{
  std::pair<std::string, ExtensionSpanExporterBuilder *> entry{name, builder};
  m_span_exporter_builders.insert(entry);
}

const ExtensionSpanProcessorBuilder *Registry::GetExtensionSpanProcessorBuilder(
    const std::string &name)
{
  ExtensionSpanProcessorBuilder *builder = nullptr;
  auto search                            = m_span_processor_builders.find(name);
  if (search != m_span_processor_builders.end())
  {
    builder = search->second;
  }
  return builder;
}

void Registry::AddExtensionSpanProcessorBuilder(const std::string &name,
                                                ExtensionSpanProcessorBuilder *builder)
{
  std::pair<std::string, ExtensionSpanProcessorBuilder *> entry{name, builder};
  m_span_processor_builders.insert(entry);
}

}  // namespace init
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
