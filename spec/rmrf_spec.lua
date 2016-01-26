local lfs  = require('lfs')
local rmrf = require('rmrf')

local isWindows
if _G.jit then
  isWindows = _G.jit.os == "Windows"
else
  isWindows = not not package.path:match("\\")
end


local shell = {}
function shell.mkdirs(p)
  if isWindows then
    os.execute('md "'..p..'"')
  else
    os.execute('mkdir -p '..p)
  end
end

function shell.rmdirs(p)
  if isWindows then
    os.execute('rd /Q /S "'..p..'"')
  else
    os.execute('rm -rf '..p)
  end
end

describe('rmrf()', function()

  before_each(function()
    shell.mkdirs('e/x/i/s/t')
    os.execute('echo 123 > e/x/i/s/t/file')
  end)
  after_each(function()
    shell.rmdirs('e')
  end)
  it('remove directory', function()
    assert.are.equal('directory', lfs.attributes('e/x/i/s/t', 'mode'))
    assert.is_true(rmrf('e'))
    assert.is_nil(lfs.attributes('e/x/i/s/t', 'mode'))
  end)

  it('returns nil if directory if already exists', function()
    assert.is_nil(rmrf('n/o/t'))
  end)
end)
