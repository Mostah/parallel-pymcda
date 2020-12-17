#include "../src/DataGenerator.h"
#include "../src/utils.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <utility>

// TEST(TestDataGenerator, TestDatasetGenerator) {
//   DataGenerator data = DataGenerator();
//   data.DatasetGenerator(3, 20, 4, "test.xml");
// }

// TEST(TestDataGenerator, TestModelGenerator) {
//   DataGenerator data = DataGenerator();
//   data.modelGenerator(2, 3, "test_model.xml");
// }

TEST(TestDataGenerator, TestXmlFileType) {
  DataGenerator data = DataGenerator();
  std::string type = data.getXmlFileType("test_model.xml");
  std::ostringstream os2;
  os2 << type;
  EXPECT_EQ(os2.str(), "model");
}

TEST(TestDataGenerator, TestXmlFileType2) {
  DataGenerator data = DataGenerator();
  std::string type = data.getXmlFileType("test.xml");
  std::ostringstream os2;
  os2 << type;
  EXPECT_EQ(os2.str(), "dataset");
}

TEST(TestDataGenerator, TestNumberOfCriteriaForModels) {
  DataGenerator data = DataGenerator();
  int crit = data.getNumberOfCriteria("test_model.xml");
  std::ostringstream os2;
  os2 << crit;
  EXPECT_EQ(os2.str(), "2");
}

TEST(TestDataGenerator, TestNumberOfCriteriaForData) {
  DataGenerator data = DataGenerator();
  int crit = data.getNumberOfCriteria("test.xml");
  std::ostringstream os2;
  os2 << crit;
  EXPECT_EQ(os2.str(), "3");
}

TEST(TestDataGenerator, TestNumberOfCategoriesForModels) {
  DataGenerator data = DataGenerator();
  int crit = data.getNumberOfCategories("test_model.xml");
  std::ostringstream os2;
  os2 << crit;
  EXPECT_EQ(os2.str(), "3");
}

TEST(TestDataGenerator, TestNumberOfCategoriesForData) {
  DataGenerator data = DataGenerator();
  int crit = data.getNumberOfCategories("test.xml");
  std::ostringstream os2;
  os2 << crit;
  EXPECT_EQ(os2.str(), "4");
}

TEST(TestDataGenerator, TestGetLambdaForData) {
  DataGenerator data = DataGenerator();
  try {
    int crit = data.getThresholdValue("test.xml");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Cannot find any threshold in xml file, "
                                      "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetLambdaForModel) {
  DataGenerator data = DataGenerator();
  float crit = data.getThresholdValue("test_model.xml");
  std::ostringstream os2;
  os2 << crit;
  EXPECT_EQ(os2.str(), "0.9425");
}

TEST(TestDataGenerator, TestGetNumerOfAlternativesForDataset) {
  DataGenerator data = DataGenerator();
  int nb_alternatives = data.getNumberOfAlternatives("test.xml");
  std::ostringstream os2;
  os2 << nb_alternatives;
  EXPECT_EQ(os2.str(), "20");
}

TEST(TestDataGenerator, TestGetNumerOfAlternativesForModel) {
  DataGenerator data = DataGenerator();
  try {
    int nb_alt = data.getNumberOfAlternatives("test_model.xml");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Cannot find the number of alternatives in xml file, "
                          "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetAlternativePerformanceForDataset) {
  DataGenerator data = DataGenerator();
  Performance p = data.getAlternativePerformance("test.xml", "alt0");
  std::ostringstream os2;
  os2 << p;
  EXPECT_EQ(os2.str(), "Performance(Perf( name : alt0, crit : crit0, value : 0 "
                       "), Perf( name : alt0, crit : crit1, value : 0 ), Perf( "
                       "name : alt0, crit : crit2, value : 0 ), )");
}

TEST(TestDataGenerator, TestGetAlternativePerformanceForModel) {
  DataGenerator data = DataGenerator();
  try {
    Performance p = data.getAlternativePerformance("test_model.xml", "alt0");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Cannot find any alternatives in xml file, "
                          "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetAlternativeIdsForDataset) {
  DataGenerator data = DataGenerator();
  std::vector<std::string> v = data.getAlternativeIds("test.xml");
  std::ostringstream os2;
  os2 << v;
  EXPECT_EQ(os2.str(),
            "[alt0,alt1,alt2,alt3,alt4,alt5,alt6,alt7,alt8,alt9,alt10,"
            "alt11,alt12,alt13,alt14,alt15,alt16,alt17,alt18,alt19]");
}

TEST(TestDataGenerator, TestGetAlternativeIdsForModel) {
  DataGenerator data = DataGenerator();
  try {
    std::vector<std::string> v = data.getAlternativeIds("test_model.xml");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Cannot find any alternatives in xml file, "
                          "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetCriteriaIdsForDataset) {
  DataGenerator data = DataGenerator();
  std::vector<std::string> v = data.getCriteriaIds("test.xml");
  std::ostringstream os2;
  os2 << v;
  EXPECT_EQ(os2.str(), "[crit0,crit1,crit2]");
}

TEST(TestDataGenerator, TestGetCriteriaIdsForModel) {
  DataGenerator data = DataGenerator();
  std::vector<std::string> v = data.getCriteriaIds("test_model.xml");
  std::ostringstream os2;
  os2 << v;
  EXPECT_EQ(os2.str(), "[crit0,crit1]");
}

TEST(TestDataGenerator, TestGetCriterionForDataset) {
  DataGenerator data = DataGenerator();
  try {
    Criterion v = data.getCriterion("test.xml", "crit1");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(
        err.what(),
        std::string(
            "Cannot find the criterion associated to its weights in xml file, "
            "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetCriterionForModel) {
  DataGenerator data = DataGenerator();
  Criterion crit1 = data.getCriterion("test_model.xml", "crit1");
  std::ostringstream os2;
  os2 << crit1;
  EXPECT_EQ(os2.str(), "Criterion(id : crit1, direction : +, weight : 0)");
}

TEST(TestDataGenerator, TestGetAlternativeAssignmentModel) {
  DataGenerator data = DataGenerator();
  try {
    int v = data.getAlternativeAssignment("test_model.xml", "alt0");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Cannot find category assignment "
                                      "associated to alternative in xml file, "
                                      "most likely have a xml model file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetCriterionCategoryLimitsDataset) {
  DataGenerator data = DataGenerator();
  try {
    std::vector<float> v = data.getCriterionCategoryLimits("test.xml", "crit1");
    FAIL() << "should have throw invalid_argument error.";
  } catch (std::invalid_argument const &err) {
    EXPECT_EQ(err.what(),
              std::string("Cannot find category limits associated to "
                          "criterion in xml file, "
                          "most likely have a xml dataset file"));
  } catch (...) {
    FAIL() << "should have throw invalid_argument error.";
  }
}

TEST(TestDataGenerator, TestGetCriterionCategoryLimitsModel) {
  DataGenerator data = DataGenerator();
  std::vector<float> v =
      data.getCriterionCategoryLimits("test_model.xml", "crit0");
  std::ostringstream os2;
  os2 << v;
  EXPECT_EQ(os2.str(), "[1.1,1.1,1.1,1.1]");
}
