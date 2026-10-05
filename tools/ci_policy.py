#!/usr/bin/env python3
"""Choose build validation and inventory maintenance independently."""
import argparse
import os


def lanes(reused, cache_hit):
    if type(reused) is not bool or type(cache_hit) is not bool:
        raise ValueError('CI proof and cache decisions require booleans')
    return {'full': not reused, 'inventory': not reused or not cache_hit}


def boolean(value):
    if value not in ('true', 'false'):
        raise argparse.ArgumentTypeError('Expected true or false')
    return value == 'true'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--reused', type=boolean, required=True)
    parser.add_argument('--cache-hit', type=boolean, required=True)
    args = parser.parse_args()
    with open(os.environ['GITHUB_OUTPUT'], 'a') as output:
        for name, enabled in lanes(args.reused, args.cache_hit).items():
            output.write(f'{name}={str(enabled).lower()}\n')


if __name__ == '__main__':
    main()
