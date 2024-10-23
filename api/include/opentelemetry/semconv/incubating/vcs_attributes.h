/*
 * Copyright The OpenTelemetry Authors
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * DO NOT EDIT, this is an Auto-generated file from:
 * buildscripts/semantic-convention/templates/registry/semantic_attributes-h.j2
 */

#pragma once

#include "opentelemetry/common/macros.h"
#include "opentelemetry/version.h"

OPENTELEMETRY_BEGIN_NAMESPACE
namespace semconv
{
namespace vcs
{

/**
 * The ID of the change (pull request/merge request) if applicable. This is usually a unique (within
 * repository) identifier generated by the VCS system.
 */
static constexpr const char *kVcsRepositoryChangeId = "vcs.repository.change.id";

/**
 * The human readable title of the change (pull request/merge request). This title is often a brief
 * summary of the change and may get merged in to a ref as the commit summary.
 */
static constexpr const char *kVcsRepositoryChangeTitle = "vcs.repository.change.title";

/**
 * The name of the <a href="https://git-scm.com/docs/gitglossary#def_ref">reference</a> such as
 * <strong>branch</strong> or <strong>tag</strong> in the repository.
 */
static constexpr const char *kVcsRepositoryRefName = "vcs.repository.ref.name";

/**
 * The revision, literally <a href="https://www.merriam-webster.com/dictionary/revision">revised
 * version</a>, The revision most often refers to a commit object in Git, or a revision number in
 * SVN. <p> The revision can be a full <a
 * href="https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-5.pdf">hash value (see glossary)</a>,
 * of the recorded change to a ref within a repository pointing to a
 * commit <a href="https://git-scm.com/docs/git-commit">commit</a> object. It does
 * not necessarily have to be a hash; it can simply define a
 * <a href="https://svnbook.red-bean.com/en/1.7/svn.tour.revs.specifiers.html">revision number</a>
 * which is an integer that is monotonically increasing. In cases where
 * it is identical to the @code ref.name @endcode, it SHOULD still be included. It is
 * up to the implementer to decide which value to set as the revision
 * based on the VCS system and situational context.
 */
static constexpr const char *kVcsRepositoryRefRevision = "vcs.repository.ref.revision";

/**
 * The type of the <a href="https://git-scm.com/docs/gitglossary#def_ref">reference</a> in the
 * repository.
 */
static constexpr const char *kVcsRepositoryRefType = "vcs.repository.ref.type";

/**
 * The <a href="https://en.wikipedia.org/wiki/URL">URL</a> of the repository providing the complete
 * address in order to locate and identify the repository.
 */
static constexpr const char *kVcsRepositoryUrlFull = "vcs.repository.url.full";

namespace VcsRepositoryRefTypeValues
{
/**
 * <a
 * href="https://git-scm.com/docs/gitglossary#Documentation/gitglossary.txt-aiddefbranchabranch">branch</a>
 */
static constexpr const char *kBranch = "branch";

/**
 * <a
 * href="https://git-scm.com/docs/gitglossary#Documentation/gitglossary.txt-aiddeftagatag">tag</a>
 */
static constexpr const char *kTag = "tag";

}  // namespace VcsRepositoryRefTypeValues

}  // namespace vcs
}  // namespace semconv
OPENTELEMETRY_END_NAMESPACE