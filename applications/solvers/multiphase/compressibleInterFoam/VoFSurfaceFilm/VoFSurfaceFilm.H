/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2021 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::fv::VoFSurfaceFilm

Description
    Surface film model for VoF simulations.

Usage
    Example usage:
    \verbatim
    VoFSurfaceFilm
    {
        libs    ("libradiationModels.so");
        type    VoFSurfaceFilm;
        phase   water;
    }
    \endverbatim

SourceFiles
    VoFSurfaceFilm.C

\*---------------------------------------------------------------------------*/

#ifndef VoFSurfaceFilm_H
#define VoFSurfaceFilm_H

#include "fvOption.H"
#include "rhoThermo.H"
#include "SLGThermo.H"
#include "surfaceFilmModel.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace fv
{

/*---------------------------------------------------------------------------*\
               Class VoFSurfaceFilm Declaration
\*---------------------------------------------------------------------------*/

class VoFSurfaceFilm
:
    public option
{
    // Private Data

        //- The name of the phase which transfers to the film
        word phaseName_;

        //- Reference to the primary region thermo
        const rhoThermo& thermo_;

        //- The SLG thermo required by the surfaceFilmModel
        SLGThermo slgThermo_;

        //- The surface film model pointer
        mutable autoPtr<regionModels::surfaceFilmModel> film_;

        //- Current time index (used for updating)
        mutable label curTimeIndex_;


public:

    //- Runtime type information
    TypeName("VoFSurfaceFilm");


    // Constructors

        //- Construct from explicit source name and mesh
        VoFSurfaceFilm
        (
            const word& sourceName,
            const word& modelType,
            const dictionary& dict,
            const fvMesh& mesh
        );

        //- Disallow default bitwise copy construction
        VoFSurfaceFilm
        (
            const VoFSurfaceFilm&
        ) = delete;


    // Member Functions

        // Checks

            //- Return the list of fields for which the option adds source term
            //  to the transport equation
            virtual wordList addSupFields() const;


        // Correct

            //- Solve the film and update the sources
            virtual void correct();


        // Add explicit and implicit contributions to compressible equation

            //- Add explicit contribution to compressible enthalpy equation
            virtual void addSup
            (
                const volScalarField& rho,
                fvMatrix<scalar>& eqn,
                const word& fieldName
            ) const;

            //- Add implicit contribution to compressible momentum equation
            virtual void addSup
            (
                const volScalarField& rho,
                fvMatrix<vector>& eqn,
                const word& fieldName
            ) const;


    // Member Operators

        //- Disallow default bitwise assignment
        void operator=(const VoFSurfaceFilm&) = delete;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace fv
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
