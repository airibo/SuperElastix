#include "selxItkMeanSquaresImageToImageMetricv4.h"

namespace selx
{
  template<int Dimensionality, class TPixel>
  ItkMeanSquaresImageToImageMetricv4Component< Dimensionality, TPixel>::ItkMeanSquaresImageToImageMetricv4Component()
{
  m_theItkFilter = TheItkFilterType::New();
  
  //TODO: instantiating the filter in the constructor might be heavy for the use in component selector factory, since all components of the database are created during the selection process.
  // we could choose to keep the component light weighted (for checking criteria such as names and connections) until the settings are passed to the filter, but this requires an additional initialization step.
}

template<int Dimensionality, class TPixel>
ItkMeanSquaresImageToImageMetricv4Component< Dimensionality, TPixel>::~ItkMeanSquaresImageToImageMetricv4Component()
{
}

template<int Dimensionality, class TPixel>
typename ItkMeanSquaresImageToImageMetricv4Component< Dimensionality, TPixel>::ItkMetricv4Pointer ItkMeanSquaresImageToImageMetricv4Component< Dimensionality, TPixel>::GetItkMetricv4()
{
  
  return (ItkMetricv4Pointer) this->m_theItkFilter;
}
template<int Dimensionality, class TPixel>
bool
ItkMeanSquaresImageToImageMetricv4Component< Dimensionality, TPixel>
::MeetsCriterion(const ComponentBase::CriterionType &criterion)
{
  bool hasUndefinedCriteria(false);
  bool meetsCriteria(false);
  if (criterion.first == "ComponentProperty")
  {
    meetsCriteria = true;
    for (auto const & criterionValue : criterion.second) // auto&& preferred?
    {
      if (criterionValue != "SomeProperty")  // e.g. "GradientDescent", "SupportsSparseSamples
      {
        meetsCriteria = false;
      }
    }
  }
  else if (criterion.first == "Dimensionality") //Supports this?
  {
    meetsCriteria = true;
    for (auto const & criterionValue : criterion.second) // auto&& preferred?
    {
      if (std::stoi(criterionValue) != Dimensionality)
      {
        meetsCriteria = false;
      }
    }

  }
  else if (criterion.first == "PixelType") //Supports this?
  {
    meetsCriteria = true;
    for (auto const & criterionValue : criterion.second) // auto&& preferred?
    {
      if (criterionValue != Self::GetPixelTypeNameString())
      {
        meetsCriteria = false;
      }
    }

  }
  return meetsCriteria;
}

} //end namespace selx