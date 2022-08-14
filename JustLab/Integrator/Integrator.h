
#pragma once


#include <Math/Vector3.h>

namespace Just
{
    struct Integrator
    {
        virtual Vector3f Sample() = 0;

        virtual Vector3f Eval() = 0;

        virtual float PDF() = 0;
    };

    struct SimpleIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct NormalIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct AOIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct WhittedStyleIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct PathMatsIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct PathEmsIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };

    struct PathMsiIntegrator : Integrator
    {
        Vector3f Sample() override;

        Vector3f Eval() override;

        float PDF() override;
    };
}