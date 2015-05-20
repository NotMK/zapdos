#include "ZapdosApp.h"
#include "Moose.h"
#include "AppFactory.h"
// #include "ModulesApp.h"

// Kernels
#include "CoeffDiffusion.h"
#include "FirstOrderReaction.h"
#include "SecondOrderReaction.h"
#include "SelfBinaryReaction.h"
#include "SrcSelfBinaryReaction.h"
#include "SrcSecondOrderReaction.h"
#include "PoissonSource.h"
#include "MatAdvection.h"
#include "IonizationSource.h"
#include "DivFreeConvection.h"
#include "CoupledIonizationSource.h"
#include "ArtificialDiff.h"
#include "ConstConvection.h"
#include "TimeDerivativeSUPG.h"
#include "ConstConvectionSUPG.h"
#include "ExampleDiffusion.h"
#include "INSMass.h"
#include "INSMomentum.h"
#include "INSTemperature.h"
#include "INSMomentumTimeDerivative.h"
#include "INSTemperatureTimeDerivative.h"
//#include "NSMassInviscidFlux.h"
//#include "NSKernel.h"
// AuxKernels

#include "EFieldMag.h"
#include "VelocityMag.h"
#include "ChargeDensity.h"
#include "IonSrcTerm.h"
#include "AlphaTimesHSize.h"
#include "HSize.h"
#include "Sigma.h"
#include "VelocityH.h"
#include "Velocity.h"

// Materials
#include "Air.h"
#include "NoCouplingAir.h"
#include "BlockAverageDiffusionMaterial.h"
#include "WD.h"
#include "Water.h"

// Indicators
#include "AnalyticalDiffIndicator.h"

// User Objects
#include "BlockAverageValue.h"

// Boundary Conditions
#include "NoDiffusiveFlux.h"

template<>
InputParameters validParams<ZapdosApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  return params;
}

ZapdosApp::ZapdosApp(const std::string & name, InputParameters parameters) :
    MooseApp(name, parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
//  ModulesApp::registerObjects(_factory);
  ZapdosApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
//  ModulesApp::associateSyntax(_syntax, _action_factory);
  ZapdosApp::associateSyntax(_syntax, _action_factory);
}

ZapdosApp::~ZapdosApp()
{
}

extern "C" void ZapdosApp__registerApps() { ZapdosApp::registerApps(); }
void
ZapdosApp::registerApps()
{
  registerApp(ZapdosApp);
}

void
ZapdosApp::registerObjects(Factory & factory)
{
  registerKernel(CoeffDiffusion);
  registerKernel(FirstOrderReaction);
  registerKernel(SecondOrderReaction);
  registerKernel(SelfBinaryReaction);
  registerKernel(SrcSelfBinaryReaction);
  registerKernel(SrcSecondOrderReaction);
  registerKernel(PoissonSource);
  registerKernel(MatAdvection);
  registerKernel(IonizationSource);
  registerKernel(DivFreeConvection);
  registerKernel(CoupledIonizationSource);
  registerKernel(ArtificialDiff);
  registerKernel(ConstConvection);
  registerKernel(TimeDerivativeSUPG);
  registerKernel(ConstConvectionSUPG);
  registerKernel(ExampleDiffusion);
  registerKernel(INSMass);
  registerKernel(INSMomentum);
  registerKernel(INSTemperature);
  registerKernel(INSMomentumTimeDerivative);
  registerKernel(INSTemperatureTimeDerivative);
//  registerKernel(NSMassInviscidFlux);
//  registerKernel(NSKernel);
  registerAux(EFieldMag);
  registerAux(VelocityMag);
  registerAux(ChargeDensity);
  registerAux(IonSrcTerm);
  registerAux(AlphaTimesHSize);
  registerAux(HSize);
  registerAux(Sigma);
  registerAux(VelocityH);
  registerAux(Velocity);
  registerMaterial(Air);
  registerMaterial(NoCouplingAir);
  registerMaterial(BlockAverageDiffusionMaterial);
  registerMaterial(WD);
  registerMaterial(Water);
  registerIndicator(AnalyticalDiffIndicator);
  registerUserObject(BlockAverageValue);
  registerBoundaryCondition(NoDiffusiveFlux);
}

void
ZapdosApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}