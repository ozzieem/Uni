function write2file(fn,varargin)
%
% ------------------------------------------------------
% | Basic Multibody Simulator Derived (Matlab toolbox) |
% ------------------------------------------------------
% | General purpose |
% -------------------
% 
% write2file
% 
% Writes data to file 
%
% Input:
% -------
% fn      - file name ('mitko.dat')
% varargin = [v1,s1,v2,s2,...] 
% v1      - variable 1
% s1      - type of variable 1
% ...
%
% Example:
% write2file('mitko.dat', [1], '%i ', 343.23, ' %5.5f \n', 'mitko', '%s')
% 
% write2file('mitko.dat') - deletes the contents of the file
%

%
% Version 1.0 [2009/07]
%
% This toolbox is developed by Dimitar Dimitrov for educational purpose.
% ----------------------------------------------------
%

n = length(varargin);

if n == 0
  fid = fopen(fn,'w');
  fprintf(fid,'');
else
  fid = fopen(fn,'a');
  for i = 1:2:n
    v = varargin{i};
    s = varargin{i+1};
    
    fprintf(fid, s, v);
  end
  fprintf(fid,' \n');
end
fclose(fid);

%%%EOF