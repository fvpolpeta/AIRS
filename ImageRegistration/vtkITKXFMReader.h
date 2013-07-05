/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkITKXFMReader.h

Copyright (c) 2006 Atamai, Inc.

Use, modification and redistribution of the software, in source or
binary forms, are permitted provided that the following terms and
conditions are met:

1) Redistribution of the source code, in verbatim or modified
   form, must retain the above copyright notice, this license,
   the following disclaimer, and any notices that refer to this
   license and/or the following disclaimer.

2) Redistribution in binary form must include the above copyright
   notice, a copy of this license and the following disclaimer
   in the documentation or with other materials provided with the
   distribution.

3) Modified copies of the source code must be clearly marked as such,
   and must not be misrepresented as verbatim copies of the source code.

THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE SOFTWARE "AS IS"
WITHOUT EXPRESSED OR IMPLIED WARRANTY INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  IN NO EVENT SHALL ANY COPYRIGHT HOLDER OR OTHER PARTY WHO MAY
MODIFY AND/OR REDISTRIBUTE THE SOFTWARE UNDER THE TERMS OF THIS LICENSE
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, LOSS OF DATA OR DATA BECOMING INACCURATE
OR LOSS OF PROFIT OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF
THE USE OR INABILITY TO USE THE SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

=========================================================================*/
// .NAME vtkITKXFMReader - A reader for ITK transformation files.
// .SECTION Description
// ITK uses a text file to save its transformations.  The file contains
// the name of the transform class and the parameters.  Not all ITK
// transform types are supported by this reader, only linear transforms
// that can be represented by a 4x4 matrix.
// .SECTION Thanks
// Thanks to David Gobbi for writing this class.

#ifndef __vtkITKXFMReader_h
#define __vtkITKXFMReader_h

#include "vtkAlgorithm.h"

class vtkAbstractTransform;
class vtkDoubleArray;
class vtkCollection;

class VTK_EXPORT vtkITKXFMReader : public vtkAlgorithm
{
public:
  vtkTypeMacro(vtkITKXFMReader,vtkAlgorithm);

  static vtkITKXFMReader *New();
  virtual void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Set the file name.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Get the entension for this file format.
  virtual const char* GetFileExtensions() {
    return ".txt"; }

  // Description:
  // Get the name of this file format.
  virtual const char* GetDescriptiveName() {
    return "ITK Transform"; }

  // Description:
  // Test whether the specified file can be read.
  virtual int CanReadFile(const char* name);

  // Description:
  // Get the number of transforms in the file.
  virtual int GetNumberOfTransforms();

  // Description:
  // Get one of the transforms listed in the file.
  virtual vtkAbstractTransform *GetNthTransform(int i);

  // Description:
  // Get the transform that results from concatenating all
  // of the transforms in the file.  This will return null
  // if you have not specified a file name.
  virtual vtkAbstractTransform *GetTransform();

  // Description:
  // Get any comments that are included in the file.
  virtual const char *GetComments();

protected:
  vtkITKXFMReader();
  ~vtkITKXFMReader();

  char *FileName;
  vtkAbstractTransform *Transform;
  vtkCollection *Transforms;
  int LineNumber;
  char *Comments;

  void SetTransform(vtkAbstractTransform *transform);

  int ReadLine(istream &infile, char result[]);
  int ReadLineAfterComments(istream &infile, char result[]);
  int SkipWhitespace(char **cpp);
  int ParseLeftHandSide(char **cpp, char identifier[]);
  int ParseStringValue(char **cpp, char data[]);
  int ParseFloatValues(char **cpp, vtkDoubleArray *array);

  int ReadTransform(istream &infile, char linetext[]);

  int CheckNumberOfParameters(
    vtkDoubleArray *parameters, vtkDoubleArray *fixedParameters,
    vtkIdType n, vtkIdType m, const char *classname);

  virtual int ReadFile();

  virtual int ProcessRequest(vtkInformation* request,
                             vtkInformationVector** inInfo,
                             vtkInformationVector* outInfo);

private:
  vtkITKXFMReader(const vtkITKXFMReader&); // Not implemented
  void operator=(const vtkITKXFMReader&);  // Not implemented

};

#endif
