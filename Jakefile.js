const path = require('path');

const CC = 'gcc';
const CFLAGS = '-Iinclude -Wall -Wextra -Werror -g';
const LDFLAGS = '-Llib -llua53 -lSDL2 -lSDL2_image';

const sources = new jake.FileList().include('src/**/*.c').toArray();
const objectFiles = sources.map(s => `build/${s.replace(/.c$/, '.o')}`);
const getSourceNameFromObject = name => name.replace(/^build\//, '').replace(/.o$/, '.c');

desc('This is the default task.');
task('default', function (params) {
  console.log('This is the default task.');
});

desc('Build');
file('kiwi', objectFiles, {async: true}, function (params) {
  const command = `${CC} ${objectFiles.join(' ')} -o ${this.name} ${LDFLAGS}`;

  console.log(command);

  jake.exec(command, () => {
    complete();
  });
});

rule('.o', getSourceNameFromObject, {async: true}, function () {
  const command = `${CC} ${CFLAGS} -c ${this.source} -o ${this.name}`;

  const dirname = path.dirname(this.name);
  jake.mkdirP(dirname);

  console.log(command);

  jake.exec(command, () => {
    complete();
  });
});

desc('Clean');
task('clean', function (params) {
  jake.rmRf('build');
  jake.rmRf('kiwi');
});
