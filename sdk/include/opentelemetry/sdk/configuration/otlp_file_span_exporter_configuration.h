// Copyright The OpenTelemetry Authors
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include <string>

#include "opentelemetry/sdk/configuration/span_exporter_configuration.h"
#include "opentelemetry/sdk/configuration/span_exporter_configuration_visitor.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace sdk
{
namespace configuration
{

// YAML-SCHEMA: schema/common.json
// YAML-NODE: ExperimentalOtlpFileExporter
class OtlpFileSpanExporterConfiguration : public SpanExporterConfiguration
{
public:
  void Accept(SpanExporterConfigurationVisitor *visitor) const override
  {
    visitor->VisitOtlpFile(this);
  }

  std::string output_stream;
};

}  // namespace configuration
}  // namespace sdk
OPENTELEMETRY_END_NAMESPACE
