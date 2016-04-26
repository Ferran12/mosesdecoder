/*
 * FeatureFunctions.h
 *
 *  Created on: 27 Oct 2015
 *      Author: hieu
 */

#ifndef FEATUREFUNCTIONS_H_
#define FEATUREFUNCTIONS_H_

#include <vector>
#include <string>
#include "../legacy/Parameter.h"
#include "FeatureRegistry.h"
#include "../Phrase.h"

namespace Moses2
{

class System;
class FeatureFunction;
class StatefulFeatureFunction;
class PhraseTable;
class Manager;
class MemPool;
class PhraseImpl;
class TargetPhrase;
class TargetPhrases;
class Scores;

namespace SCFG
{
class TargetPhrase;
}

class FeatureFunctions
{
public:
  std::vector<const PhraseTable*> m_phraseTables;

  FeatureFunctions(System &system);
  virtual ~FeatureFunctions();

  const std::vector<const FeatureFunction*> &GetFeatureFunctions() const
  {
    return m_featureFunctions;
  }

  const std::vector<const StatefulFeatureFunction*> &GetStatefulFeatureFunctions() const
  {
    return m_statefulFeatureFunctions;
  }

  const std::vector<const FeatureFunction*> &GetWithPhraseTableInd() const
  {
    return m_withPhraseTableInd;
  }

  size_t GetNumScores() const
  {
    return m_ffStartInd;
  }

  void Create();
  void Load();

  const FeatureFunction *FindFeatureFunction(const std::string &name) const;
  const PhraseTable *GetPhraseTablesExcludeUnknownWordPenalty(size_t ptInd);

  // the pool here must be the system pool if the rule was loaded during load, or the mgr pool if it was loaded on demand
  void EvaluateInIsolation(MemPool &pool, const System &system,
      const Phrase<Moses2::Word> &source, TargetPhrase &targetPhrase) const;
  void EvaluateAfterTablePruning(MemPool &pool, const TargetPhrases &tps,
      const Phrase<Moses2::Word> &sourcePhrase) const;

protected:
  std::vector<const FeatureFunction*> m_featureFunctions;
  std::vector<const StatefulFeatureFunction*> m_statefulFeatureFunctions;
  std::vector<const FeatureFunction*> m_withPhraseTableInd;
  boost::unordered_map<std::string, size_t> m_defaultNames;
  System &m_system;
  size_t m_ffStartInd;

  FeatureFunction *Create(const std::string &line);
  std::string GetDefaultName(const std::string &stub);

  FeatureRegistry m_registry;
};

}

#endif /* FEATUREFUNCTIONS_H_ */
